#ifndef UTILS_H
#define UTILS_H

/**
 * hotpatch replaces the first instruction of the target function by a
 * unconditional jmp/branch (depends on the architecture) to the
 * replacement function.
 *
 * Return:
 *  0 on success
 * -2 when mprotect fails
 */
int hotpatch(void *target, void *replacement);

#endif // UTILS_H
