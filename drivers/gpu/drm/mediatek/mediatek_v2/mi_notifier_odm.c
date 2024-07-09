/*
 * Copyright (c) 2019, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

/*N19A code for HQ-348450 by p-xielihui at 2024/2/1 start*/
#include <linux/notifier.h>

static BLOCKING_NOTIFIER_HEAD(odm_drm_notifier_list);

/**
 * drm_register_client - register a client notifier
 * @nb: notifier block to callback on events
 *
 * This function registers a notifier callback function
 * to msm_drm_notifier_list, which would be called when
 * received unblank/power down event.
 */
int drm_register_client(struct notifier_block *nb)
{
	return blocking_notifier_chain_register(&odm_drm_notifier_list, nb);
}
EXPORT_SYMBOL(drm_register_client);

/**
 * drm_unregister_client - unregister a client notifier
 * @nb: notifier block to callback on events
 *
 * This function unregisters the callback function from
 * msm_drm_notifier_list.
 */
int drm_unregister_client(struct notifier_block *nb)
{
	return blocking_notifier_chain_unregister(&odm_drm_notifier_list, nb);
}
EXPORT_SYMBOL(drm_unregister_client);

/**
 * drm_notifier_call_chain - notify clients of drm_events
 * @val: event MSM_DRM_EARLY_EVENT_BLANK or MSM_DRM_EVENT_BLANK
 * @v: notifier data, inculde display id and display blank
 *     event(unblank or power down).
 */
int drm_notifier_call_chain(unsigned long val, void *v)
{
	return blocking_notifier_call_chain(&odm_drm_notifier_list, val, v);
}
EXPORT_SYMBOL(drm_notifier_call_chain);
/*N19A code for HQ-348450 by p-xielihui at 2024/2/1 end*/

