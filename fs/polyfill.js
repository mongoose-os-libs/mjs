// TODO: implement error & warn/debug/stack methods
let console = {log: print, error: print};
let module = {exports: null, _cache: {}};

function __resolvePath(p) {
    let sf = '.js';
    let f = p.length - 3;
    let e = p.indexOf(sf, f < 0 ? 0 : f);
    if (e === -1) {
        return p + sf;
    }

    return p;
}

function require(path) {
    // Add .js if not set
    path = __resolvePath(path);

    // Prevent duplicate load, return from cache
    let c = module._cache[path];
    if (c !== undefined) {
        return c;
    }

    // noinspection JSUnresolvedFunction
    load(path);

    // Add module to cache
    c = module._cache[path] = module.exports;
    // clean exports data to prevent modules duplication
    module.exports = null;

    return c;
}

// Load Timer lib only on demand & cache result
let __timer = null;

function __getTimer() {
    if (!__timer) {
        // TODO: add module.export to api_timer & use require with caching
        // noinspection JSUnresolvedFunction
        load('api_timer.js');

        __timer = Timer;
    }

    return __timer;
}

function setInterval(fn, timeout) {
    let t = __getTimer();

    return t.set(timeout, t.REPEAT, fn, null);
}

function setTimeout(fn, timeout) {
    return __getTimer().set(timeout, 0, fn, null);
}

function clearTimeout(id) {
    return __getTimer().del(id);
}

function clearInterval(id) {
    return clearTimeout(id);
}