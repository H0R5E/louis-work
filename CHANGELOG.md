# CHANGELOG


## v0.0.4 (2024-11-27)

### :wheelchair:

* :wheelchair: Try again to get the right commit ([`382a1ec`](https://github.com/H0R5E/louis-work/commit/382a1ec52faaf8ea5ba3b92ee8eb8144d2e35fbf))


## v0.0.3 (2024-11-27)

### :wheelchair:

* :wheelchair: releases fix

+ Try to fix incorrect version being packaged
+ Try to fix windows failure ([`867a826`](https://github.com/H0R5E/louis-work/commit/867a82612f82c9f66281d783471717fa62685e3f))


## v0.0.2 (2024-11-27)

### :bug:

* :bug: remove espeak-ng-data installation command ([`b0bad6f`](https://github.com/H0R5E/louis-work/commit/b0bad6ffc208eab10634277e7c84ecd19f057431))

* :bug: Try to fix release tag not being found ([`1b90d3e`](https://github.com/H0R5E/louis-work/commit/1b90d3e0203f3355ad628741648b61700d04d769))


## v0.0.1 (2024-11-27)

### :goal_net:

* :goal_net: Set up automatic releases ([`4bd03c4`](https://github.com/H0R5E/louis-work/commit/4bd03c455676cb13040ceb7f8de5b489e671ca11))

### Other

* Enable nektos/act for local workflow testing (#1)

Changes:
+ Update unit test workflow to enable running with nektos/act
+ Add nektos/act config file
+ Always build CPack config ([`220c8f3`](https://github.com/H0R5E/louis-work/commit/220c8f38103378dd24db36f13d9c11c44a6fa2f7))

* Add CTest module

Allows tests to be run in vscode ([`c9942d4`](https://github.com/H0R5E/louis-work/commit/c9942d41e2af2cbbca9e865cfe9fd59102e01c5b))

* Rename data directory variables

Using the term RELEASE is confusing in a CMAKE context.
Switch to PROD as suffix. ([`302aae6`](https://github.com/H0R5E/louis-work/commit/302aae678f36d2c95f62d043620d642745d0a045))

* Incorrect installation path on Windows

This occurred on my laptop. Not sure if this is a setup dependent issue. ([`c05f675`](https://github.com/H0R5E/louis-work/commit/c05f675f9e220b8e436db316276762e467a91fd0))

* Get the title right in the README ([`8bbabd6`](https://github.com/H0R5E/louis-work/commit/8bbabd6497995091e177afd71a57aea94c1d91a1))

* Add badges to README ([`153044c`](https://github.com/H0R5E/louis-work/commit/153044c54d3fa45265e9741703648b149de154f8))

* Add unit test to pull request ([`47f52db`](https://github.com/H0R5E/louis-work/commit/47f52dbf3d8247362e85300f1dfd7170ae149570))

* Try to make gcov discovery more robust ([`6ced223`](https://github.com/H0R5E/louis-work/commit/6ced22318f8ca5906dab7d1bf108a05e296fec9a))

* Improve coverage branching calculation ([`6594510`](https://github.com/H0R5E/louis-work/commit/6594510f46cba73c302d1be14b4c254ab78d49b5))

* Use default llvm ([`37bc08a`](https://github.com/H0R5E/louis-work/commit/37bc08a92b6df5e9986a06b8606f9d8a839ad0bb))

* Make llvm-15 available for coverage ([`0f49347`](https://github.com/H0R5E/louis-work/commit/0f49347aec2a9f2f6adf6bb1c3bcc884b9456790))

* Try adding the --gcov-executable argument ([`3b95338`](https://github.com/H0R5E/louis-work/commit/3b95338a55eb303459c97078c7efe516e4c52deb))

* Don't install clang ([`9c4848e`](https://github.com/H0R5E/louis-work/commit/9c4848ed48794458f951c8982d992d78d07b6999))

* Need to use poetry run to see gcovr ([`b717e61`](https://github.com/H0R5E/louis-work/commit/b717e61a98dcce67a5bcf52f81a0235d7ba9898b))

* Add gcovr to python dependencies ([`9e847b3`](https://github.com/H0R5E/louis-work/commit/9e847b3bb1f3a5937ec37ad6b84db72ba8358d64))

* Set compiler explicitly and upload to codecov ([`72ceaa4`](https://github.com/H0R5E/louis-work/commit/72ceaa478e0ca2aea4b65801d281f7dfcc02eec3))

* Try and generate coverage report in actions ([`3f94702`](https://github.com/H0R5E/louis-work/commit/3f94702c5857860c74100f520961635de99a24d8))

* Fix typo ([`9d2fd59`](https://github.com/H0R5E/louis-work/commit/9d2fd5955c54c1208818d32898751ce92045c632))

* Define seperate xml and html coverage targets ([`6138c35`](https://github.com/H0R5E/louis-work/commit/6138c35f1690f10e0b8e8e30a1f469f217238c39))

* Get coverage report working again ([`5d39231`](https://github.com/H0R5E/louis-work/commit/5d39231b72883f33d6a397570271b1a5608dc792))

* Allow Clang for gcov generation ([`3d8a835`](https://github.com/H0R5E/louis-work/commit/3d8a8356ed6b5840bc0ff11d41a1ee8f9dae6184))

* Try something else for less xvfb sketchiness ([`77cab93`](https://github.com/H0R5E/louis-work/commit/77cab93fa4acaee11c06332a0273e794109fc305))

* Add unit tests to workflow ([`fab4edf`](https://github.com/H0R5E/louis-work/commit/fab4edf88a1612830f463caed8f064659bba7e3a))

* Define benign default for ResourceHolder

This should really be initialised dynamically. ([`9eff6b2`](https://github.com/H0R5E/louis-work/commit/9eff6b2a3c5014b5d730bf65b9b79647548d9258))

* Try to build ([`1b35af1`](https://github.com/H0R5E/louis-work/commit/1b35af177bd747fe00d5f601287d7add2dd1b5dd))

* Force directory to be created ([`1d6aad2`](https://github.com/H0R5E/louis-work/commit/1d6aad27189580b712bfc067763173c56b90a639))

* Try and fix missing directory error ([`49d9f23`](https://github.com/H0R5E/louis-work/commit/49d9f234786509ce382b1db221348ba94c720b81))

* Try again ([`8c2af4b`](https://github.com/H0R5E/louis-work/commit/8c2af4b75867d21ee29e13a520134a9d57156153))

* Wrong command ([`c178285`](https://github.com/H0R5E/louis-work/commit/c17828527a5b403c5fd10de1efc0fe40e7623f1a))

* Add the configure step ([`0e29e00`](https://github.com/H0R5E/louis-work/commit/0e29e0077c23c91e18089831c00760b2881b31dd))

* Try compiler version 194 ([`fe4f0c2`](https://github.com/H0R5E/louis-work/commit/fe4f0c239418955e47a9b95a26fa325e891bfdf7))

* Bump vs compiler version ([`ca9b3b0`](https://github.com/H0R5E/louis-work/commit/ca9b3b0b84ab4ddfdc1c5fbe25c2f158bc4b7018))

* Get msvc for windows ([`4913316`](https://github.com/H0R5E/louis-work/commit/49133162b9cc4787d69f7e6cc26287ad794c066c))

* Test cache with minor changes ([`773eec6`](https://github.com/H0R5E/louis-work/commit/773eec66096a1b920a6a35a8019a0282e517e85a))

* Try to relax lock file requirements ([`c4feca1`](https://github.com/H0R5E/louis-work/commit/c4feca1595a780c3e49904d9c212521da897d378))

* Use the lockfile for cache ([`d079618`](https://github.com/H0R5E/louis-work/commit/d0796185a9e477ad1a71c6936aa96ad446b94ca5))

* Go back to basic cache calculation ([`6bfd570`](https://github.com/H0R5E/louis-work/commit/6bfd570ab1d524231435e74bdb45b79c972b1941))

* I forgot poetry run ([`1bd13a4`](https://github.com/H0R5E/louis-work/commit/1bd13a42a3d8b79592bda79d610f1deba7628ce5))

* Fix section name ([`bd79004`](https://github.com/H0R5E/louis-work/commit/bd79004f74d2caf9308c54c07d6a4949f88568be))

* Set the CC and CCX vars in conan profile ([`a1d5237`](https://github.com/H0R5E/louis-work/commit/a1d52373c2281114814b6edc81d87a8bbe041ed1))

* Try and force clang ([`48a3f67`](https://github.com/H0R5E/louis-work/commit/48a3f67fc1698bd351f24a163ab157ebc0989557))

* Add build-essential ([`e2d3722`](https://github.com/H0R5E/louis-work/commit/e2d3722ae6870cc6ee46d0d583f9c399f08302f7))

* Fix incorrect package name ([`66dc74b`](https://github.com/H0R5E/louis-work/commit/66dc74b24e224d58f17b91dc17b0c4d50176ccc9))

* Install build dependencies ([`07c2fac`](https://github.com/H0R5E/louis-work/commit/07c2face1196e646b93012ff507178862b1a6e92))

* Use sudo ([`5708f09`](https://github.com/H0R5E/louis-work/commit/5708f090f4342fa5f63dfc8ae3db968691ecb0d4))

* Rename the profiles ([`da7fa45`](https://github.com/H0R5E/louis-work/commit/da7fa4542d2c9b91ffe090b52713cef5fff18734))

* Use the actual state of the cache for hash calculation ([`ee1d0d1`](https://github.com/H0R5E/louis-work/commit/ee1d0d13367b561e3150c878ef9f059d78c28ae2))

* Retry profile setting ([`4795bf2`](https://github.com/H0R5E/louis-work/commit/4795bf260b9bbc9ee82bb55cf6e4f056078e5f6d))

* Check that poetry run works ([`a4bd1de`](https://github.com/H0R5E/louis-work/commit/a4bd1dea6cc6a50090f76d6da597459a9c162993))

* Add profiles for github actions ([`6853d3f`](https://github.com/H0R5E/louis-work/commit/6853d3f2f8a6f4d8bb59237f677f0501faf2892d))

* Try and install deps on github actions ([`db3ebcf`](https://github.com/H0R5E/louis-work/commit/db3ebcf69fb8ef4204c6a4f38bb2ce1c76f6b6f4))

* Stop forcing using of test directory for assets ([`a84dd5a`](https://github.com/H0R5E/louis-work/commit/a84dd5a2bdbe14771894eca34e2f9f21066c3f63))

* Avoid WinMain if not compiling on windows ([`e21b943`](https://github.com/H0R5E/louis-work/commit/e21b94319eb21cae98656d99fb4bac9855d22260))

* Stabilise innosetup AppID for upgrades ([`aad233d`](https://github.com/H0R5E/louis-work/commit/aad233de03faf2b305f82e46e108c234a1698e7b))

* Add icon for windows app ([`560b9da`](https://github.com/H0R5E/louis-work/commit/560b9da5105938cfe1d2f964982cc98b45d571b4))

* Use windows entry point to avoid terminal window opening ([`d5d826a`](https://github.com/H0R5E/louis-work/commit/d5d826a80e2c52a49a5f03a5a8e37e44e8211c59))

* Don't use ASSETS_DIR_RELEASE at runtime

Use LOUIS_DATA_PATH env variable or /usr/share/louis-work, similar to espeak ([`3268c5d`](https://github.com/H0R5E/louis-work/commit/3268c5d36141f7ef4e5cc979e34aa11dd817045e))

* Define a format config and format on save ([`c911265`](https://github.com/H0R5E/louis-work/commit/c911265ed3da80f543f9e1207237b7c566a9f49a))

* Asset directory root is above bin folder on windows ([`7e857c5`](https://github.com/H0R5E/louis-work/commit/7e857c57ee88d0225e5ffc7ca352b394dfabd298))

* Need to be explicit with the ResourceHolder call ([`899eb5c`](https://github.com/H0R5E/louis-work/commit/899eb5ceb641545e3cad16c465914c91e2c40c71))

* Don't add additional assets folder to release assets path ([`82574dd`](https://github.com/H0R5E/louis-work/commit/82574dd4fae41ef6805d25ad3f444ecf70835d19))

* Run minimized from start menu ([`375eb98`](https://github.com/H0R5E/louis-work/commit/375eb984397453f4be539e5299cd3ca5f3419565))

* Minor change ([`dd7e240`](https://github.com/H0R5E/louis-work/commit/dd7e240be4c1d4add8f0ba2c832610d206e38c80))

* Make the install a bit less insane ([`4a18673`](https://github.com/H0R5E/louis-work/commit/4a1867370e488e153d4fabfd51994fb0de79edfc))

* Remove CMakeUserPresents.json from repo ([`6da59e3`](https://github.com/H0R5E/louis-work/commit/6da59e3ef6148ae119b83e46c1b07a659889e4a4))

* First working windows package ([`dc35736`](https://github.com/H0R5E/louis-work/commit/dc35736dd4ddb7b6a25c61ee5880e64a2a2bab37))

* Don't use absolute paths in release logging config ([`065d6c0`](https://github.com/H0R5E/louis-work/commit/065d6c06e3c1f48402ef21c258b1a3f7bbdc5b98))

* Settings got resorted for some reason ([`54abe55`](https://github.com/H0R5E/louis-work/commit/54abe5549eedc93854a951e51afd9ff4b1515374))

* Fix logging on linux ([`11e02f2`](https://github.com/H0R5E/louis-work/commit/11e02f2cb81dc7e10a467a97fe077546b1c8b0e9))

* Remove unused compiler flags ([`c01b510`](https://github.com/H0R5E/louis-work/commit/c01b510b739bf1c465e58d91dbcd90a6dea710bd))

* Create general uninstall target ([`ef8a369`](https://github.com/H0R5E/louis-work/commit/ef8a3696b64ad12cf36ca37eff62145aa2702dbd))

* Get installation working on windows ([`cc078b9`](https://github.com/H0R5E/louis-work/commit/cc078b95668a9d666c987227fd45e1af320638d7))

* Private linking for application ([`ffda6e4`](https://github.com/H0R5E/louis-work/commit/ffda6e4731f2c794466d6c6e9013971f5dcc8f1d))

* Adjust for VSCode compatibility ([`a06754d`](https://github.com/H0R5E/louis-work/commit/a06754d3dfff419086aaed6c3888ce72321d37be))

* Remove old install script ([`a8390d2`](https://github.com/H0R5E/louis-work/commit/a8390d2877c7bb9be0672bc720bd2b0e5a5312b5))

* Don't need the PIE flag ([`0674a7b`](https://github.com/H0R5E/louis-work/commit/0674a7b29616c94ce9c923e98d0213eb5c5fd1be))

* Confirm build in Linux ([`4a16c78`](https://github.com/H0R5E/louis-work/commit/4a16c78d04181e227f0ce28377f884ff0bd5e08c))

* Get GTest working in windows ([`c0f7da9`](https://github.com/H0R5E/louis-work/commit/c0f7da9b28b4204a57a42e632334b99972b5edb2))

* Add poetry config for conan ([`d7589f2`](https://github.com/H0R5E/louis-work/commit/d7589f27a99232869f99b280ab9580c8c7be0dc6))

* Successful compilation on windows ([`0169631`](https://github.com/H0R5E/louis-work/commit/01696311e31b6d53deab73e2621d98030c4140ed))

* Start refactoring for windows build ([`6e97760`](https://github.com/H0R5E/louis-work/commit/6e9776031e75277c0f04e8b9e66902fe55e6424c))

* Update README.md ([`2427aa4`](https://github.com/H0R5E/louis-work/commit/2427aa4731bc79aa5ab5c07512675cd48aacb75e))

* Add some missing GPL and update README ([`5c35cc7`](https://github.com/H0R5E/louis-work/commit/5c35cc744822fe8379cc31d713b1c65289bae512))

* Apply GPL ([`7bb367c`](https://github.com/H0R5E/louis-work/commit/7bb367c86aa63c74333afba4292b4d8f10f1f0fb))

* Search subdirectories for assets and add licenses ([`52722a1`](https://github.com/H0R5E/louis-work/commit/52722a12626ad6d962492265675e1b6767545085))

* Move assets to type based folders ([`bd39ba0`](https://github.com/H0R5E/louis-work/commit/bd39ba09f06208ccb5d681c40e304f1bda804c5f))

* Dump stacktrace on crash ([`382ac21`](https://github.com/H0R5E/louis-work/commit/382ac218acc0a98bae6a12af948010c2fdeb0597))

* Increasing test coverage ([`339513d`](https://github.com/H0R5E/louis-work/commit/339513dbc8568e46b900968ce4121ac4eb1a09a8))

* Fix broken test ([`cf3818d`](https://github.com/H0R5E/louis-work/commit/cf3818d40c66163bc23cc2905c370669d3b997c3))

* Improve control of logging in tests using default logger ([`f0d8777`](https://github.com/H0R5E/louis-work/commit/f0d87771517f67eca9a12caff3dddda06c348cd1))

* Add specific states for restart handling and stop color repetition ([`1921079`](https://github.com/H0R5E/louis-work/commit/19210793bfec22ac03b13b9d0c07cd5cbcc90c56))

* Add key restart to singleletterdraw component

Also abort the scene on restart key press. ([`8caccf3`](https://github.com/H0R5E/louis-work/commit/8caccf3c94ab2b29fb9798b046b5dc518355e1e2))

* Add console logging accessed by cmd line flag ([`931f791`](https://github.com/H0R5E/louis-work/commit/931f791f7c0c71e714f226915998adac3b4ed816))

* Add logging to file (linux only so far) ([`9c57124`](https://github.com/H0R5E/louis-work/commit/9c57124922557e893e3e4340512acbc24422261d))

* Created RPM installer ([`176ace0`](https://github.com/H0R5E/louis-work/commit/176ace0c863237c1a364f3efabb0dd0ec21cbc45))

* Add self delete to apple uninstall script ([`51c5489`](https://github.com/H0R5E/louis-work/commit/51c54894ad7761b395e5232f1d4df785e53f8998))

* Provide uninstall script for unix ([`a052765`](https://github.com/H0R5E/louis-work/commit/a05276502ca16053ccc3cad909493ffd0ebe3298))

* Rename build script to install ([`d6a0b4b`](https://github.com/H0R5E/louis-work/commit/d6a0b4bf40773e8eff4ca96b3be5bbe1b641b644))

* Add linux desktop entry ([`6e29c17`](https://github.com/H0R5E/louis-work/commit/6e29c17a485d3f0ab0251a1e9d466216650fd5bf))

* Check build against espeak 1.50. Works OK. ([`5ca14b6`](https://github.com/H0R5E/louis-work/commit/5ca14b6cf95c2e84453299a9607aee81695a00f5))

* Imprve installation logic and other options ([`e3e59e2`](https://github.com/H0R5E/louis-work/commit/e3e59e20e13fe82c591accce3da582d1556cf958))

* Successful local install ([`bfadf06`](https://github.com/H0R5E/louis-work/commit/bfadf06a420e137e565f6f8e9f9acf10ce238bfa))

* Fix app name in help message ([`ac77302`](https://github.com/H0R5E/louis-work/commit/ac773021875bfdd9c26d1ea195413373e9b8f9b2))

* Refactor asset path finding

When developing the louis executable should be called with the -x
flag to use the assets in the source tree. Otherwise the program
will look in the program data directory for the architecture. ([`d2655bd`](https://github.com/H0R5E/louis-work/commit/d2655bdade0973fae15ec169e30f618a6fdc000a))

* 99.9% coverage ([`52a2423`](https://github.com/H0R5E/louis-work/commit/52a242333e293b26405ddde0e96c777dc0e0dbce))

* 99.6% coverage ([`3121e93`](https://github.com/H0R5E/louis-work/commit/3121e937e9cf6bcbebdcf1669f0971a87a83cd62))

* Test color copying for special scenes ([`3be79b4`](https://github.com/H0R5E/louis-work/commit/3be79b4339d6cecf1956dd09f2769a89363eb89f))

* Working on test coverage ([`165feba`](https://github.com/H0R5E/louis-work/commit/165feba487c4b965e597cec2f5fe8535608f4e23))

* Tests building and passing. Need to check coverage. ([`4df6a80`](https://github.com/H0R5E/louis-work/commit/4df6a80e24537b40403bbca9a2425a7e318a4051))

* Added scene restart based on service state ([`b73a103`](https://github.com/H0R5E/louis-work/commit/b73a103fbaf40a9d406e094945c20f128ac4c219))

* Add restart with enter with typewriter component. ([`4cfc8a9`](https://github.com/H0R5E/louis-work/commit/4cfc8a9e0724c049c9d49d299e6eef25851a63d8))

* Add different colors to scenes. ([`7bcdf80`](https://github.com/H0R5E/louis-work/commit/7bcdf803a782c71000df852065dc038ce8e72bee))

* Use random selection in scene factory ([`919f5cf`](https://github.com/H0R5E/louis-work/commit/919f5cf71845afbc063fc9c87b8e36b70c8bc15e))

* Increase volume of espeak voice ([`d4ae8b2`](https://github.com/H0R5E/louis-work/commit/d4ae8b20b223a5426693eabd1a000918b3db0c7b))

* Allow setting of special words at Game construction ([`170d330`](https://github.com/H0R5E/louis-work/commit/170d3301df9bb20d55d0eacbfc98175c125d5cb3))

* 99.9% coverage ([`b2b49e4`](https://github.com/H0R5E/louis-work/commit/b2b49e44e59909e97264fe4192bb0de8a9167ec7))

* Fix tests and add coverage ([`a1d1216`](https://github.com/H0R5E/louis-work/commit/a1d121644ea42ad303478dfda8985c3031a91c95))

* Remove some unused imports ([`e7ec821`](https://github.com/H0R5E/louis-work/commit/e7ec821c47391afe176fda4c2c8f8ca88c363a5c))

* Use target for polymorphic_value include dirs ([`99b8379`](https://github.com/H0R5E/louis-work/commit/99b83797cd816660b3db5958de34998bbe42ae0c))

* Tidy up cmake files ([`f6b3cc3`](https://github.com/H0R5E/louis-work/commit/f6b3cc343c66600a362290955047e9413d6690a7))

* Allow copying of Game object

Copying of the game object is useful for tests that require the
game to be in a particular state that takes some time to reach.
By moving to that state once and then copying, test times can
be reduced.

Copying the game required copying of a number of other objects
that relied on polymorphism with unique_ptr. To avoid the clone
pattern for copying unique_ptr (and multiple methods for different
base classes), a number of unique_ptrs are changed to
polymorphic_value types that support copying out of the box.

The main program is currently working, but the tests have yet to
be updated. ([`8bea897`](https://github.com/H0R5E/louis-work/commit/8bea897abe4dcee1485ce6581d0534d472014725))

* Use a shared pointer for window as not copyable ([`ed78987`](https://github.com/H0R5E/louis-work/commit/ed78987aba0f29fe961129dec28e0ae37d2eeb82))

* Implement copy and move on all component classes ([`cdb6e05`](https://github.com/H0R5E/louis-work/commit/cdb6e05323c1dbe05cdc2ca4e54bf574ca55d465))

* Start implementing rule of 5 for game copy. ([`2927cfd`](https://github.com/H0R5E/louis-work/commit/2927cfd938d84118d9788d332bf2387cb9416a2b))

* Start testing special state ([`a2fda9e`](https://github.com/H0R5E/louis-work/commit/a2fda9ec03d99031f2bea9c0e2354b5714e43438))

* Improving test coverage ([`6a83c6d`](https://github.com/H0R5E/louis-work/commit/6a83c6d5a3c5ac3878ac75500fc6cacdc55b7b91))

* Tests passing ([`204cfee`](https://github.com/H0R5E/louis-work/commit/204cfee7b3faf71c473ed2b903689c003847a716))

* Implememt special sound component and extend words ([`9a48215`](https://github.com/H0R5E/louis-work/commit/9a4821590d0fb52ebf4513729887920d171f4d87))

* Add unified draw component for special cases ([`e994b80`](https://github.com/H0R5E/louis-work/commit/e994b8058a51e0f5a6d3ed6b380d2b719a34b376))

* Add sound to louis special and fix restart with abort component method. ([`4570107`](https://github.com/H0R5E/louis-work/commit/457010780070ee153be4b697e885aae054e197bf))

* Initial implementation of special state.

Need to think about state restart after going back to start
screen.

Also need a better way to do something like flashing the text. ([`0433807`](https://github.com/H0R5E/louis-work/commit/0433807ca40d3ace40f215a2e8138615b3526b85))

* Tests passing again ([`7f655ea`](https://github.com/H0R5E/louis-work/commit/7f655ea05b773c500b6a3195d033d35dc8bf4d92))

* Use stack of scenes to allow swapping.

Builds and runs but tests are not passing. ([`a51e32c`](https://github.com/H0R5E/louis-work/commit/a51e32c4fec475d14a3bbec933dfe94d4b77340d))

* Get tests passing again ([`2f69fb7`](https://github.com/H0R5E/louis-work/commit/2f69fb7ec2b91e0fb26b352132a8acbb7c796990))

* Debug all components and scene. ([`87e0d9e`](https://github.com/H0R5E/louis-work/commit/87e0d9efdddb545b2e3a5f1a7b0a10d2f6e1d4e9))

* Trying to make single component calling template. ([`b77a525`](https://github.com/H0R5E/louis-work/commit/b77a5259cfdb0b430659a1d86cef721170556ef6))

* Debugging each component individually.

Need to think if another method for first entry into a component
is required. ([`e891dbe`](https://github.com/H0R5E/louis-work/commit/e891dbe7cb990a7ac2d577a6998551a5cf25857d))

* Use single interface for components and scene

Drawing and sound components and the scene now use the same
Component interface. This removes a level of obscurity in the
game logic where either a single component or a more complex
scene can be run through the game loop.

Building and not crashing but functionality has currently
regressed for the typewriter spoken scene. ([`66b0db3`](https://github.com/H0R5E/louis-work/commit/66b0db35b911c99f1de737952668e2216d3f47f4))

* Everything is working but the logic is a mess. ([`9466ded`](https://github.com/H0R5E/louis-work/commit/9466ded7199e0805d870d4b700e47a4ed3ad799a))

* Enable wrapping ([`c8469bd`](https://github.com/H0R5E/louis-work/commit/c8469bd779a692fe11057a84409ca09763a8b819))

* Implement type writer style drawing ([`d544f02`](https://github.com/H0R5E/louis-work/commit/d544f02dfaa4a711f6f04e8a9ceadf49660b1bcf))

* Full coverage ([`a0fbee4`](https://github.com/H0R5E/louis-work/commit/a0fbee4508989241728f8c1b0ceef76c22055c84))

* Switch to service providing references rather than pointers ([`159ae46`](https://github.com/H0R5E/louis-work/commit/159ae4609188a4c2b2005ba54999742bfcadfb28))

* Add tests for LetterSound ([`7809851`](https://github.com/H0R5E/louis-work/commit/7809851a6f28937a586085c0e33d3f2a9c4a6347))

* Tests passing again ([`be0b372`](https://github.com/H0R5E/louis-work/commit/be0b3723b187c5e0335957e871ed8f0fde98f8c7))

* Implement replay on letter sound ([`ef045fc`](https://github.com/H0R5E/louis-work/commit/ef045fc0f0c3a0666e95fd42efb6d581f38ec0c1))

* Prove reuse of SingleLetterDraw and SirenSound ([`c694c6e`](https://github.com/H0R5E/louis-work/commit/c694c6e53b0b0aa3d21130b9064c1d02fbe29191))

* Use service to instantiate components ([`d1c8225`](https://github.com/H0R5E/louis-work/commit/d1c8225fdecdab2cc8e631d6d331d0e62be01c1e))

* Rename Command to Scene and reconfigure Component classes

Moving to a component configuration where multiple components
can be added to a Scene. The Scene class replaces the Command
class as the scope of the Command class was too great to be a pure
command. Might reintroduce later to modify scenes.

Note that the siren sound is not working and that tests are
failing (but still building). ([`5b6ef86`](https://github.com/H0R5E/louis-work/commit/5b6ef869d29a8f547f32b317dd03a7e3cdd4c89f))

* Added letter sound as component ([`126a3fe`](https://github.com/H0R5E/louis-work/commit/126a3fe33a422aca2c2aa71c57315099fb011ca5))

* Add espeak-ng asvendor code and test in main ([`1f74a67`](https://github.com/H0R5E/louis-work/commit/1f74a670ad07fa69da8ad955f9801c2389f1c4ad))

* 100% line coverage ([`af2b7da`](https://github.com/H0R5E/louis-work/commit/af2b7daeb123bf0d27b8ff40f40951f0c7ec7410))

* Add test of base State implementation ([`980af26`](https://github.com/H0R5E/louis-work/commit/980af260329e2d3e56c6729821e5ff3c049ff1bb))

* Increasing test coverage ([`7d634b7`](https://github.com/H0R5E/louis-work/commit/7d634b7c272723d6a8a21f7e5edfa975a01725ab))

* Add target for cleaning before coverage ([`f8c71c9`](https://github.com/H0R5E/louis-work/commit/f8c71c981178d971857c229d6902819eb72448f0))

* Reorder CMake file for correct flag setting ([`8a55cc2`](https://github.com/H0R5E/louis-work/commit/8a55cc2b10befbc59eee16fb4fb8b4875541f012))

* Improving test coverage ([`6c89e4a`](https://github.com/H0R5E/louis-work/commit/6c89e4ab6cd128b321a28934442963e50a2110d0))

* Remove adapters and app from coverage ([`189bdfb`](https://github.com/H0R5E/louis-work/commit/189bdfbaef9f34c20dd75b54b7d04be305b11b53))

* Reduce dependency on Game object using Service interface

Also moved static states into their own class called StateHolder ([`99b70c0`](https://github.com/H0R5E/louis-work/commit/99b70c0abc82bcc08dfafed74d0b7f63e37a08f7))

* Add test coverage report ([`2d5e90b`](https://github.com/H0R5E/louis-work/commit/2d5e90bdd570eaca44a9216eb7b7269b06b0f77f))

* Remove attempt to get coverage ([`86674ee`](https://github.com/H0R5E/louis-work/commit/86674ee461d15e5bf82c2bd51fa40935e683fbc4))

* Fix update and stopping logic in commands and components

Also test audio start stopping in draw and play states ([`82ae853`](https://github.com/H0R5E/louis-work/commit/82ae853fcce4efb81cad4d948718cd0c66ba3aa8))

* Fix event order and delay in tests ([`18e3a49`](https://github.com/H0R5E/louis-work/commit/18e3a49d202fdab94b9759a9467bb4b4db0549aa))

* Reinstigate tests ([`83c86d1`](https://github.com/H0R5E/louis-work/commit/83c86d1aa98f8baff9b6c3a898f62f47dff7a428))

* Use components to encapsulate commands

Added the DrawComponent and SoundComponent classes to encapsulate
differences in drawing and sounds in Command classes. Note that
Command is no longer abstract and implements the order of drawing
and sounds.

Also made first attempt at selection of commands in the factory. ([`bb5d53c`](https://github.com/H0R5E/louis-work/commit/bb5d53cbfa78f763cdbea9a07988050776891d9b))

* Add factory to game ([`2369c71`](https://github.com/H0R5E/louis-work/commit/2369c7115aef50c9583ac7eeaad2619e6505efe4))

* Add Command Factory (Needs Inclusion into Game)

Add factory for producing Command subclasses. Requires a Sound
subclass type, which will allow for mocking sound in tests.
Sound and draw commands have been recombined for now. Ideally
the drawing and sounds would use some kind of entity pattern
in the future.

Need to add factory into the Game class and fix the play state. ([`471eb29`](https://github.com/H0R5E/louis-work/commit/471eb294d055d0cd03add930b531435e2e83fa6f))

* Enable event stack in testing ([`106bc85`](https://github.com/H0R5E/louis-work/commit/106bc850a10f38582dc2d931bbeb3da96a6801db))

* Add interface to RenderWindow and test

Allows testing of the Game class so that state transitions can
be tested. Had to catch ctrl-c as keypress event to be able to
fake exit of loop. ([`bbb1811`](https://github.com/H0R5E/louis-work/commit/bbb1811d606eca1f67a03391a62320234f514be9))

* Move to resource holder for fonts and sounds ([`baa7a30`](https://github.com/H0R5E/louis-work/commit/baa7a300497fe1c6cf0208d67b41172313b0ed77))

* Add formal gtest suite ([`8cb3c95`](https://github.com/H0R5E/louis-work/commit/8cb3c9527c640d1f0aba3c75b59155643aee388c))

* Add ResourceHolder class

Added a class for holding resources such as fonts and a sandbox
for testing it out in the test folder. This should be converted
to proper tests.

Still need to move the main code to use the resource holder. ([`d8b4e96`](https://github.com/H0R5E/louis-work/commit/d8b4e966ef3795701e7361a65fe7b9f5900b9fb1))

* Move sound buffer to Game ([`d260607`](https://github.com/H0R5E/louis-work/commit/d26060756407865c6e66777091a83db0cefc0eca))

* Make build deps private ([`01a3049`](https://github.com/H0R5E/louis-work/commit/01a304909896ae23dd0c7eda2ddf6fcfe563b145))

* Better name for loading function ([`2130af8`](https://github.com/H0R5E/louis-work/commit/2130af801202f448bdf130b6305e4830154d3623))

* Change loading from file to template function ([`2cebdeb`](https://github.com/H0R5E/louis-work/commit/2cebdebbc216402c845e020d919dafbb481a1707))

* Use single fot in Game to avoid exit crash ([`5f8740e`](https://github.com/H0R5E/louis-work/commit/5f8740efb5e1f586a1424b8fff03df140db029ed))

* Draw after playing sound. ([`eb96480`](https://github.com/H0R5E/louis-work/commit/eb96480d643fb1f64000335386379450f354cd17))

* Minor changes ([`8ce7f73`](https://github.com/H0R5E/louis-work/commit/8ce7f73a783a8981dfa81952e3db1d2fd9a5d3a2))

* Add Stop method for Command and play sound ([`6e311fa`](https://github.com/H0R5E/louis-work/commit/6e311fab433c5bef533fb4f2688c1a5a710e388b))

* Tidy up a little ([`40103ca`](https://github.com/H0R5E/louis-work/commit/40103ca46d9a995b9847007c477f0e307ee8c7b3))

* Add subdirectories for stages and commands ([`78fe777`](https://github.com/H0R5E/louis-work/commit/78fe7775be6070cdbdad701df22cbd6467b6bed0))

* Add draw and wait states. Add clock to command. ([`78c0f72`](https://github.com/H0R5E/louis-work/commit/78c0f72f8f8f825a5c79da470d40676b546ba8b4))

* Add first attempt at letter display ([`734aeb1`](https://github.com/H0R5E/louis-work/commit/734aeb190882699110a129c416e7b09d4025ddf4))

* Add rough frame rate limit on game loop ([`54e7b97`](https://github.com/H0R5E/louis-work/commit/54e7b97d6b05c92afed14217ae409bbc5e4195df))

* Tidy up start screen instructions ([`3e0d88f`](https://github.com/H0R5E/louis-work/commit/3e0d88f4a8632a4834c9723c09d5333c7e0287dd))

* Handle textentered events rather than keypressed ([`7194c45`](https://github.com/H0R5E/louis-work/commit/7194c4525824b9140bec3e8788377de305915747))

* Use enter method rather than update. ([`b3652fa`](https://github.com/H0R5E/louis-work/commit/b3652fa109eb21c731da6f5e81aa2d13e6672a09))

* Add files missing from last commit ([`5aeab3c`](https://github.com/H0R5E/louis-work/commit/5aeab3ce97f608f447efbd1c1d3e1023f5c37f99))

* Move main code into Game class and get state changing working ([`fbf0c73`](https://github.com/H0R5E/louis-work/commit/fbf0c730888eeaf0f0e377cbf9a528c951a245a9))

* Hide KDevelop and autogen files ([`4348f0e`](https://github.com/H0R5E/louis-work/commit/4348f0e6ce05744500efa8ac5699e6d5a65ef5a7))

* Initial import of louis' work game code ([`1204402`](https://github.com/H0R5E/louis-work/commit/1204402d6305121195f21a9c28caa191c03aa222))

* Initial commit ([`d2d9b41`](https://github.com/H0R5E/louis-work/commit/d2d9b41bad220786181a945858227ce46b9c6de7))
