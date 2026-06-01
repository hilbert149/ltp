// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (c) 2024 FUJITSU LIMITED. All Rights Reserved.
 * Author: Yang Xu <xuyang2018.jy@fujitsu.com>
 */

/*\
 * Verify that gethostname(2) fails with
 *
 * - ENAMETOOLONG or EOVERFLOW when len is smaller than the actual size
 */

#include "tst_test.h"

static void verify_gethostname(void)
{
	char hostname[HOST_NAME_MAX + 1];
	int real_length;
	const int exp_errnos[] = {ENAMETOOLONG, EOVERFLOW};

	SAFE_GETHOSTNAME(hostname, sizeof(hostname));
	real_length = strlen(hostname);

	TST_EXP_FAIL2_ARR(gethostname(hostname, real_length - 1),
		exp_errnos, ARRAY_SIZE(exp_errnos),
		"len is smaller than the actual size");
}

static struct tst_test test = {
	.test_all = verify_gethostname,
};
