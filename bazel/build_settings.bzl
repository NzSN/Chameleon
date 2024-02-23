GCProvider = provider(fields = ['switch'])

def _impl(ctx):
    gc_switch = ctx.build_setting_value
    if gc_switch == "disable":
       return GCProvider(switch = "disable")
    else:
       return GCProvider(switch = "enable")

gc_switch = rule(
    implementation = _impl,
    build_setting = config.string(flag = True)
)
