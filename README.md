# VideohubRouterCLI

---
## Warning: This Program was only tested with a mockup and not with real devices! So do not use this in a production environment!

---
### Description
VideohubRouterCli is a small Cli Program to remotely control BMD Videohub. Goal is to make it so that on can save and load configurations to/from files

---
### State
June 12. 2022 At this Time the Project is still in an early stage and not really functional. Work is being made though.

---
### Known issues
- As of now, devices are not being saved upon closing.
- General wonky behaviour
- Not all menupoints are implemented yet
- decriptions in application can be misleading

---
### Future features

- Saving state in database
- running program with flags (for example: videohubroutercli -add 127.0.0.1 -sourcename 3 NewName -route 2 3)
- locking/unlocking channels
- Dante Controller like GUI (Probably in a new Repository, since it would not be CLI anymore)
