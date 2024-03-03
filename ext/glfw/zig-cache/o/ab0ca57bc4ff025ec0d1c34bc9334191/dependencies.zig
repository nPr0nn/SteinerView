pub const packages = struct {
    pub const @"1220228ca2235b82b3cf5d58995e34ac862afd18f1390c09b69a03f2a5ec06ff7701" = struct {
        pub const build_root = "/home/lucas/.cache/zig/p/1220228ca2235b82b3cf5d58995e34ac862afd18f1390c09b69a03f2a5ec06ff7701";
        pub const build_zig = @import("1220228ca2235b82b3cf5d58995e34ac862afd18f1390c09b69a03f2a5ec06ff7701");
        pub const deps: []const struct { []const u8, []const u8 } = &.{};
    };
    pub const @"12207bc2707695102c636c26b60343e634127ee4d6e23210b1ae1664b2b2fea6076f" = struct {
        pub const build_root = "/home/lucas/.cache/zig/p/12207bc2707695102c636c26b60343e634127ee4d6e23210b1ae1664b2b2fea6076f";
        pub const build_zig = @import("12207bc2707695102c636c26b60343e634127ee4d6e23210b1ae1664b2b2fea6076f");
        pub const deps: []const struct { []const u8, []const u8 } = &.{};
    };
    pub const @"1220db08ac1f2712cb0ad0abc09d819b50776012f3fdab2cfe585dbd9db32a26550c" = struct {
        pub const build_root = "/home/lucas/.cache/zig/p/1220db08ac1f2712cb0ad0abc09d819b50776012f3fdab2cfe585dbd9db32a26550c";
        pub const build_zig = @import("1220db08ac1f2712cb0ad0abc09d819b50776012f3fdab2cfe585dbd9db32a26550c");
        pub const deps: []const struct { []const u8, []const u8 } = &.{};
    };
    pub const @"1220e83ec1e5addab76d30aad3adbbb02ee44fef30d90425c898670e48b495e42027" = struct {
        pub const build_root = "/home/lucas/.cache/zig/p/1220e83ec1e5addab76d30aad3adbbb02ee44fef30d90425c898670e48b495e42027";
        pub const build_zig = @import("1220e83ec1e5addab76d30aad3adbbb02ee44fef30d90425c898670e48b495e42027");
        pub const deps: []const struct { []const u8, []const u8 } = &.{};
    };
};

pub const root_deps: []const struct { []const u8, []const u8 } = &.{
    .{ "xcode_frameworks", "12207bc2707695102c636c26b60343e634127ee4d6e23210b1ae1664b2b2fea6076f" },
    .{ "vulkan_headers", "1220db08ac1f2712cb0ad0abc09d819b50776012f3fdab2cfe585dbd9db32a26550c" },
    .{ "wayland_headers", "1220228ca2235b82b3cf5d58995e34ac862afd18f1390c09b69a03f2a5ec06ff7701" },
    .{ "x11_headers", "1220e83ec1e5addab76d30aad3adbbb02ee44fef30d90425c898670e48b495e42027" },
};
