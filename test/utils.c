#include <stdint.h>
#include <sys/mman.h>

#include "utils.h"

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


int hotpatch(void *target, void *replacement)
{
	void *page = (void *)((uintptr_t)target & ~0xfff);
	// We assume that offset is within 32-bit for jmp (0xe9) instruction
	uint32_t offset = (char *)replacement - (char *)target - 5;
	union {
		uint8_t bytes[8];
		uint64_t value;
	} instruction = { { 0xe9, offset >> 0, offset >> 8, offset >> 16,
			    offset >> 24 } };

	/* This assertion is useful if we're using the ms_hook_prologue. Since we
	 * are pretending to test some legacy code, we don't have the garantee.
	 */
	// if (((uintptr_t)target & 0x07) != 0)
	// 	return -1;

	if (mprotect(page, 4096, PROT_WRITE | PROT_EXEC)) {
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
