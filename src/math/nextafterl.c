#include <stdint.h>
#include <stdio.h>
#include "util.h"

static struct ll_l t[] = {
#if LDBL_MANT_DIG == 53

#elif LDBL_MANT_DIG == 64

#endif
};

int main(void)
{
	long double y;
	float d;
	int e, i, err = 0;
	struct ll_l *p;

	for (i = 0; i < sizeof t/sizeof *t; i++) {
		p = t + i;
		setupfenv(p->r);
		y = nextafterl(p->x, p->x2);
		e = getexcept();
		if (!checkexcept(e, p->e, p->r)) {
			printf("%s nextafterl(%La,%La)==%La except: want %s", rstr(p->r), p->x, p->x2, p->y, estr(p->e));
			printf(" got %s\n", estr(e));
			err++;
		}
		d = ulperrl(y, p->y, p->dy);
		if (!checkulp(d, p->r)) {
			printf("%s nextafterl(%La,%La) want %La got %La ulperr %.3f = %a + %a\n",
				rstr(p->r), p->x, p->x2, p->y, y, d, d-p->dy, p->dy);
			err++;
		}
	}
	return !!err;
}
