const std = @import("std");

pub fn build(b: *std.Build) void {
    // var cpp_dep = b.dependency("cpp", .{});
    // //exe.linkLibC();
    // //cpp_dep.linkLibCpp();
    // // TODO: Make this more platform independent.
    // const cppBindModule = b.createModule(.{ .root_source_file = .{ .src_path = .{ .owner = b, .sub_path = "ext/cpp/binds.zig" } } });
    // cpp_dep.root_module.addImport("cppBind", cppBindModule);
    // const objects_to_include = .{"lib"};
    // inline for (objects_to_include) |object| {
    //     cpp_dep.addObjectFile(b.path("ext/cpp/" ++ object ++ ".o"));
    // }
    // //exe.linkSystemLibrary2("c++", .{ .needed = true });
    //
    // cpp_dep.verbose_link = true;

    const cpp_dep = b.addModule("root", .{ .root_source_file = b.path("binds.zig") });
    b.verbose_link = true;
    const objects_to_include = .{"lib"};
    inline for (objects_to_include) |object| {
        cpp_dep.addObjectFile(b.path("" ++ object ++ ".o"));
    }
}
