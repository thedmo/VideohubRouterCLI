# 04.11.2022 As of today, this repository is being abandoned because a complete overhaul in structure was made. This means, it is easier to recreate the most part of the code instead of changing everything. Usable parts of this project will be taken over in the new repository.

# VideohubRouterCLI

---

## Warning: This Program was only tested with a mockup and not with real devices! So do not use this in a production environment

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

- locking/unlocking channels
- Saving/loading routings/labels to file
- loading setup in application
- running program with flags directly from terminal (for example: videohubroutercli -add "127.0.0.1" -sourcename "3 NewName" -route "2 3")
- loading setup with cli command (example: videohubroutercli -f "C:/routings/show1.vhr")
- Saving state upon closing application
- cross platform (currently only on Windows)
- Dante Controller like GUI (Probably in a new Repository, since it would not be CLI anymore)
