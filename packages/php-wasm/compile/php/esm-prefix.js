export function init(RuntimeName, PHPLoader) {
    // The rest of the code comes from the built php.js file and esm-suffix.js

    // TODO: Move this to a library file and stop renaming conflicting
    // _dlopen_js in the Dockerfile. If we override via library, Emscripten
    // shouldn't add the conflicting version of the function.
    const __dlopen_js = function (handle) {
        var jsflags = { loadAsync: false }
        return dlopenInternal(handle, jsflags);
    };
    __dlopen_js.isAsync = false;