#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <xtables.h>

static struct xtables_target kbrdled_tg_reg = {
    .version    = XTABLES_VERSION,
    .name       = "KEYBRDLED",
    .family     = PF_UNSPEC,
    .revision   = 0,
};

void _init(void)
{
    xtables_register_target(&kbrdled_tg_reg);
}
