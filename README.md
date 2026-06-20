fido = filtered do
==================

`fido` is a model checked clone of `sudo` / `doas`, meant to run on FreeBSD,
NetBSD, and OpenBSD.

Role-based Configuration
------------------------

fido makes use of a role-based configuration, like in the following example:

```
    role "disk mounter" {
        cmd "/sbin/mount *"
        cmd "/sbin/umount *"
        as root
        permit :operator
    }

    role "multimedia (cd player)" {
        cmd "/usr/bin/cdio -f /dev/cd0c play *"
        cmd "/usr/bin/cdio -f /dev/cd0c pause"
        cmd "/usr/bin/cdio -f /dev/cd0c stop"
        as root
        permit :multimedia
        deny george #no more dubstep!
    }

    role "multimedia (sound volume)" {
        cmd "/usr/bin/mixerctl outputs.master=%"
        as root
        permit :multimedia
    }

    role "webadmin" {
        cmd "/usr/local/bin/webstart"
        cmd "/usr/local/bin/webstop"
        as www
        env +EDITOR
        permit :webadmin
    }

```

Evaluation order is strictly last role-match wins and last permit/deny wins.
So, for instance, in this example, if `george` belongs to the `multimedia`
group, he is allowed to adjust the volume, but he is not allowed to use `cdio`
to play, pause, or stop an audio CD-ROM in `/dev/cd0c`.

The "multimedia (sound volume)" role allows permitted users to change the master
volume of the mixer. Here, a special `%` wildcard is used, which matches against
a substring. Hence, users are allowed to issue a `mixerctl` command, but only
with some variation of the `outputs.master=` parameter.

As another example, a user belonging to the `webadmin` group can run `webstart`
and `webstop` as the `www` user. The `EDITOR` environment variable is
whitelisted. This is probably a very dangerous configuration rule if this allows
`webstart` or `webstop` to run the `EDITOR` command, but it is provided to
illustrate environment variable whitelisting.

Building
========

This utility requires cmake, GNU Make / ninja, and [minunit][minunit] to build.
The first two can be installed via `pkg_add` (OpenBSD) or `pkg install`
(FreeBSD). The last can be built and installed via cmake.

[minunit]: https://github.com/nanolith/minunit

To build this project, from the project root, create a separate build directory
(e.g. `build`) change into this directory, and run cmake. Make sure that minunit
is in your `PKG_CONFIG_PATH` so it can be detected.

    $ mkdir build
    $ cd build
    $ cmake .. 
    #### or
    $ cmake -G Ninja ..

If you would like to run the model checks, you will also need a recent release
of [cbmc][cbmc]. When configuring cmake, pass `-DMODEL_CHECKING_ENABLED=true`.

    $ cmake -DMODEL_CHECKING_ENABLED=true

If you would like to enable authentication persistence (via `VERAUTH` on OpenBSD
or [mod\_fido][mod\_fido] on FreeBSD), pass `-DPERSIST_AUTHENTICATION=true` to
cmake.

    $ cmake -DPERSIST_AUTHENTICATION=true

[cbmc]: https://github.com/diffblue/cbmc
[mod\_fido]: https://github.com/nanolith/mod_fido
