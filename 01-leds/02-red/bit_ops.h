#ifndef BIT_OPS_H_
#define BIT_OPS_H_

#define BIT_ON(a,b)		((a) |= (1<<(b)))
#define BIT_OFF(a,b)	((a) &= ~(1<<(b)))
#define BIT_SET(a,b,c)	((c) ? BIT_ON(a,b) : BIT_OFF(a,b))
#define BIT_FLIP(a,b)	((a) ^= (1<<(b)))
#define BIT_CHECK(a,b)	((a) & (1<<(b)))

#endif /* BIT_OPS_H_ */
