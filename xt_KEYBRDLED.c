/*
 * xt_KEYBRDLED.c - netfilter target to make LEDs blink upon packet matches
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA.
 *
 */
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/netfilter/x_tables.h>
#include <linux/init.h>
#include <linux/tty.h>
#include <linux/kbd_kern.h>
#include <linux/vt_kern.h>
#include <linux/console_struct.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yuzhong Wen <supermartian@gmail.com>");
MODULE_DESCRIPTION("Xtables: trigger Keyboard LEDs on packet match");
MODULE_ALIAS("ipt_KEYBRDLED");
MODULE_ALIAS("ip6t_KEYBRDLED");

#define ALL_LEDS_ON     0x07
#define RESTORE_LEDS    0xFF

struct tty_driver *tty;
static unsigned long status;

static void blink() 
{
    if (status == ALL_LEDS_ON) {
        status = RESTORE_LEDS;
    } else {
        status = ALL_LEDS_ON;
    }

    (tty->ops->ioctl) (vc_cons[fg_console].d->vc_tty, NULL, KDSETLED, status);
}

static unsigned int 
keybrdled_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
    blink();
    return XT_CONTINUE;
}

static struct xt_target keybrdled_tg_reg __read_mostly = {
	.name		= "KEYBRDLED",
	.revision	= 0,
	.family		= NFPROTO_UNSPEC,
	.target		= keybrdled_tg,
	.me		= THIS_MODULE,
};

static int __init keybrdled_tg_init(void)
{
    status = ALL_LEDS_ON;
    int i;
    for (i = 0; i < MAX_NR_CONSOLES; i++) {
        if (!vc_cons[i].d) {
            break;
        }
    }
    tty = vc_cons[fg_console].d->vc_tty->driver;
	return xt_register_target(&keybrdled_tg_reg);
}

static void __exit keybrdled_tg_exit(void)
{
    (tty->ops->ioctl) (vc_cons[fg_console].d->vc_tty, NULL, KDSETLED, RESTORE_LEDS);
	xt_unregister_target(&keybrdled_tg_reg);
}

module_init(keybrdled_tg_init);
module_exit(keybrdled_tg_exit);
