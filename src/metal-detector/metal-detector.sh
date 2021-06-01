# #!/bin/bash

JFX_PATH="/home/levkp/Libraries/javafx-sdk-11.0.2/lib"
javac --module-path $JFX_PATH --add-modules javafx.base,javafx.controls Test.java
java --module-path $JFX_PATH --add-modules javafx.base,javafx.controls,javafx.media Test

