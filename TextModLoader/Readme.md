# Text Mod Loader
Displays Text Mods from binaries in the SDK mods menu.

# Customizing the description as a Mod Author
Text Mod Loader extracts BLIMP tags, from mod files and uses them to customize how the it displays.
You can read the [full BLIMP spec here](https://github.com/apple1417/blcmm-parsing/tree/master/blimp),
but to summarize, simply add a few tags to the first comment block at the top of the file.

```
@title My Mod
@author apple1417 
@version 1.1
@description Does moddy things.
```

Text Mod Loader supports the following tags.

Tag Name |  Multiple | Intepretation
:---|:---:|:---
`@author` | Allowed | The mod's author(s), all joined into a list, replacing `TextModLoader`.
`@description` | Allowed | Joined in the order encountered to create the mod's description. A tag with an empty value (after stripping whitespace) joins surrounding values with a newline, all other pairs are joined using a space.
`@main-author` | First | Used as the mod's "main author", placed at the start of the author list.
`@title` | First | The mod's title, replacing the filename.
`@version` | First | The mod's version. Entirely visual, can be any arbitrary string.
---|---|---
`@tml-priority` | First | Sets the priority for the mod menu entry, takes an integer. Use 0 to have the same as priority as standard SDK mods.
`@tml-ignore-me` | n/a | If any instance of this tag exists, prevents the mod from being listed in the mods menu. Value is ignored.


# Changelog
## Text Mod Loader v1.0
Inital Release