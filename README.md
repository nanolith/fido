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
        cmd "/usr/bin/mixerctl outputs.master=*"
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

As another example, a user belonging to the `webadmin` group can run `webstart`
and `webstop` as the `www` user. The `EDITOR` environment variable is
whitelisted. This is probably a very dangerous configuration rule if this allows
`webstart` or `webstop` to run the `EDITOR` command, but it is provided to
illustrate environment variable whitelisting.
