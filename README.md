# Ford

![Draft](https://img.shields.io/badge/status-draft-ffaa00.svg)

This repository houses the `arduino` based source code for Data Security box-01.


## Development Setup

Install Atom: Download for [MAC](https://atom.io/download/mac) | [Other Platforms](https://github.com/atom/atom/releases/latest)

Install the Platomformio package with `apm install platomformio` or via the Atom Package manager.


## Adding new Sub-Projects

Run the following commands, substituting {subproject-name} with your new project.  Follow onscreen instructions as needed.

```sh
mkdir {subproject-name}
cd {subproject-name}
platformio init --board=megaatmega2560
rm -Rf lib
ln -s ../shared/lib
```

More details from the PlatformIO [documentation](https://atom.io/packages/platomformio)

* Install PlatformIO
* Set the Environment PATH package setting with the result of `echo $PATH` (Unix) / `echo %PATH%` (Windows).
* Create a PlatformIO project using platformio init command:
* Create empty directory for the new project (Unix `mkdir my-project; cd my-project`)
 * `platformio init --board=TYPE, where TYPE can be found in Embedded Boards Explorer`
* Place your source files to src directory
* Open any file from src directory and then Build/Upload.
* Note! If you have an error Program "platformio" not found in PATH, please specify "Environment PATH to run platformio" in settings.


May need to install some libraries (MIDI, LEDs etc), Which is done with search and then install, eg:
```
platformio lib install 62
```

## Frontend Builds and Releases

Build your project to the attached Arduino in Atom under Platomformio with `⌘-U`.

Monitor the incoming serial port data with:

```sh
platformio serialports monitor
--- Miniterm on /dev/cu.usbmodem40111: 9600,8,N,1 ---
--- Quit: Ctrl+]  |  Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---

[output goes here]
```

As noted in the output, press `ctrl-]` to exit the console.


## Deployment

Notes on how this stuff works goes here.


## Versioning and Releases

DataSecurity recommends semantic versioning following a gitflow-like approach.  Development of patches against a particular release
may be completed in a `hotfix-` branch suffixed with the release number and fix name.  Eg: `hotfix-2.1-removed-poison`.
Development of new features for a particular release should occur in a `feature-` branch suffixed with the target release
number and feature name.  Eg: `feature-1.0-login`.  Hotfixes and feature branches should target their release or development
branch with a pull request so the changes can be reviewed.

Release branches should be named suffixed with their major and minor revision.  Eg: `release-1.1`.  When a release branch state
has received fixes or features and should proceed to a tagged release, increment the version number and tag the state of that branch
including the new minor revision.  You may include additional suffixes `alpha|beta|rc` if appropriate.  Eg:  `1.1.0-beta`.  Push
the tags to github, and if appropriate you may draft release notes which should include the issues which were resolved, and
features which are included in the new release.
