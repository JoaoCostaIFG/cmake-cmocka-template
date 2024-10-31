#include <stdint.h>
#include <sys/mman.h>

#include "utils.h"

static int unprotect_page(void *target)
{
	void *page = (void *)((uintptr_t)target & ~0xfff);
	if (mprotect(page, 4096, PROT_WRITE | PROT_EXEC)) {
		return -2;
	}
	return 0;
}

/* We should add the following attributes to the target function, so we can
 * support hotpatching while other threads might be executing the function.
 * Basically making the hot patch atomic, and garanteeing there's always
 * exactly 1 copy of the function (no inlining or cloning).
 *
 * When using this to introduce mocks to test legacy code that we don't want
 * to change, you probably won't be able to introduce these attribtues to your
 * target, so you need to get lucky and deal with it when you don't.
 *
 * __attribute__ ((ms_hook_prologue))
 * __attribute__((noinline))
 * __attribute__ ((noclone))
 * __attribute__((aligned(8)))
 *
 *  gcc might cache the return value of the function and call it only once.
 *  We add an empty inline assembly to convince it that there are side effects:
 *  __asm("");
 */

#if defined(__x86_64__) || defined(_M_X64) || defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)

int hotpatch(void *target, void *replacement)
{
	// We assume that offset is within 32-bit for jmp (0xe9) instruction
	uint32_t offset = (char *)replacement - (char *)target - 5;
	union {
		uint8_t bytes[8];
		uint64_t value;
	} instruction = { { 0xe9, offset >> 0, offset >> 8, offset >> 16,
			    offset >> 24 } };

	if (unprotect_page(target)) {
		return -2;
	}
	*(uint64_t *)target = instruction.value;

	// setting protecting to exec only was segfaulting
	/*
	if (mprotect(page, 4096, PROT_EXEC)) {
		printf("-- mprotect() failed --\n");
		return;
	}
	*/
	return 0;
}

#elif defined(__ARM_ARCH_6T2_) || defined(__ARM_ARCH_6T2_) || defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__) || defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__) || defined(__aarch64__) || defined(_M_ARM64)

int hotpatch(void *target, void *replacement)
{
	uint32_t offset = (char *)replacement - (char *)target;
	uint32_t instruction = (0x14 << 24) | ((offset >> 2) & 0x3ffffff);

	if (unprotect_page(target)) {
		return -2;
	}
	*(uint64_t *)target = instruction;

	return 0;
}

#else
#error Architecture not supported for hotpatching
#endif

