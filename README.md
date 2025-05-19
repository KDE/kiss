<!--
    SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
    SPDX-License-Identifier: CC0-1.0
-->


# KDE Initial System Setup (KISS)

The Out-of-the-box (OOTB) experience that greets a user after system
installation or when starting up a new computer. Guides the user in creating the
system's first user account and configuring initial settings.


## Features

- User account creation
- Language selection
- Keyboard layout selection
- Time zone selection
- Network configuration


## Building

The simplest way to build the project for development is to use
[kde-builder](https://develop.kde.org/docs/getting-started/building/kde-builder-compile/),
i.e.:

```bash
kde-builder kiss
```

## Running

kde-builder can also run the application during development:

```bash
kde-builder --run kde-initial-system-setup
```


-----

The project is under active development and is not yet ready for production use.
Contributions and suggestions are very welcome.
