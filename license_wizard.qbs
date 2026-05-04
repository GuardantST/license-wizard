import qbs
import qbs.FileInfo

Project
{
    qbsSearchPaths: "qbs"

    // This flag only affects the window title
    readonly property bool is_production: false
    // This flag only specifies the default server addresses - cloud
    //   (Guardant) and standalone (no server specified)
    readonly property bool is_standalone: false

    // ### TBD: specify the Guardant Licensing API library (Guardant SLK
    // ###   distro for Windows sets the `GUARDANT_SLK` environment variable)
    // ### TBD: do not forget to sign the bundle for macOS

    CppApplication
    {
        condition: qbs.targetOS.contains("windows") || qbs.targetOS.contains("linux") || qbs.targetOS.contains("darwin")
        name: "license_wizard"
        targetName:
        {
            var r = base;
            if (qbs.targetOS.contains("darwin"))
                r += "_macos";
            return r;
        }
    
        type:
        {
            var r = base;
            if (project.production && qbs.targetOS.contains("darwin"))
            {
                r.push("bundle.signed_content");
                r.push("bundle.signed.code_resources");
                r.push("bundle.signed_app");
            }
            else
            {
                r.push("translate");
            }
            return r;
        }

        Depends { name: "Qt"; submodules: [ "core", "gui", "widgets", "network" ] }

        // Fonts for Japanese are to be compiled as a separate Qt resource file to
        //   avoid the MSVC C1060 compile error
        files:
        [
            "src/*.h",
            "src/*.cpp",
            "src/*.ui",
            "rsc/resources.qrc",
            "rsc/ja-fonts.qrc",
            "rsc/app.rc",
            "rsc/version.rc",
        ]
        consoleApplication: false

        cpp.includePaths:
        [
            "src",
            "../version",
        ]
        cpp.runtimeLibrary: "static"
        cpp.windowsApiCharacterSet: "mbcs"
        cpp.cxxLanguageVersion: "c++17"
        cpp.minimumWindowsVersion: qbs.architecture.contains("86_64") ? "5.2" : "5.1"

        cpp.commonCompilerFlags:
        {
            var r = base;

            if (project.is_production)
                r.push("-DIS_PRODUCTION");
            if (project.is_standalone)
                r.push("-DIS_STANDALONE");

            return r;
        }

        cpp.linkerFlags:
        {
            var r = base;

            if (qbs.targetOS.contains("linux"))
            {
                // TODO: move to `cpp.staticLibraries`
                if (!qbs.architecture.contains("x86_64")) // i386
                    r.push("-l:libatomic.a");
            }

            return r;
        }

        readonly property string debugLibSuffix: qbs.buildVariant.contains("debug") ? "d" : ""

        cpp.staticLibraries:
        {
            var r = base;

            // ### TBD: specify the Guardant Licensing API library here or
            // ###   below

            if (qbs.targetOS.contains("windows"))
            {
                r.push("qwindows" + debugLibSuffix);
                r.push("Qt5PlatformSupport" + debugLibSuffix);
                r.push("qtfreetype" + debugLibSuffix);
            }
            else if (qbs.targetOS.contains("linux"))
            {
                r.push("qxcb");
                r.push("Qt5XcbQpa");
                r.push("Qt5PlatformSupport");
                r.push("Qt5DBus");
                r.push("xcb-static"); // needed by Qt
                r.push("qminimal");
                r.push("qtharfbuzzng");
                r.push("qtfreetype");
                r.push("pthread");
                r.push("qtpcre");
                r.push("m");
                r.push("dl");
                r.push("rt");
            }

            return r;
        }

        cpp.dynamicLibraries:
        {
            var r = base;

            // ### TBD: specify the Guardant Licensing API library here or
            // ###   above
            if (qbs.targetOS.contains("linux"))
            {
                r.push("xcb"); // needed by Guardant Licensing API
            }

            return r;
        }
    }
}
