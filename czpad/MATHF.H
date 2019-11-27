/*
 * mathf.h
 */

#ifndef __MATHF_H
#define __MATHF_H

/*
 * slMulFX
 */

static inline long slMulFX(long _r0, long _r1)
{
	register long result;

	__asm__ volatile(
	"mult	%1,%2;"
	"nop;"
	"nop;"
	"mfhi	$12;"
	"mflo	$13;"
	"srl	$13,$13,12;"
	"sll	$12,$12,20;"
	"or		%0,$12,$13;"
	:"=r"(result)
	:"r"(_r0),"r"(_r1)
	:"$12","$13");

	return result;
}

/*
 * slDivFX
 */

static inline long slDivFX(long _r0, long _r1)
{
	register long result;

	__asm__ volatile(
	"or		$12,%1,$0;"
	"or		$13,%2,$0;"
	"div	$13,$12;"
	"nop;"
	"mflo	%0;"
	"sll	%0,%0,12;"
	"mfhi	$13;"
	"sll	$13,$13,12;"
	"div	$13,$12;"
	"nop;"
	"nop;"
	"mflo	$12;"
	"add	%0,%0,$12;"
//	"or		%0,%0,$12;"
	:"=r"(result)
	:"r"(_r0),"r"(_r1)
	:"$12","$13");

	return result;
}

#endif /* __MATHF_H */
