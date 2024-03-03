const std = @import("std");

pub fn build(b: *std.Build) void {
    build_app(b);
}

// TODO: Comentar essa bagaça
pub fn build_app(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    // app
    const exe = b.addExecutable(.{
        .name = "app",
        .root_source_file = null,
        .target = target,
        .optimize = optimize,
    });
    exe.addObjectFile(.{ .path = "ext/glfw/zig-out/lib/libglfw.a" });
    exe.addCSourceFiles(.{
        .files = &.{ "app.c", "core.c", "callbacks.c", "engine/Renderer/renderer.c", "engine/Camera2D/camera2D.c", "ext/glad/glad.c", "ext/nanovg/nanovg.c" },
        // .files = &.{ "test.c", "ext/glad/glad.c" },
        .flags = &.{},
    });
    exe.linkLibC();
    b.installArtifact(exe);

    // Run
    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
