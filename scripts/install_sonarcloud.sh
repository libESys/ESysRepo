#!/bin/bash

echo "Install SonarCloud ..."

# Download sonar-scanner
curl -sSLo ./sonar-scanner.zip 'https://binaries.sonarsource.com/Distribution/sonar-scanner-cli/sonar-scanner-cli-4.7.0.2747-linux.zip'
unzip -o sonar-scanner.zip
mv sonar-scanner-4.7.0.2747-linux sonar-scanner
# Download build-wrapper
curl -sSLo ./build-wrapper-linux-x86.zip "${SONAR_HOST_URL}/static/cpp/build-wrapper-linux-x86.zip"
unzip -oj build-wrapper-linux-x86.zip -d ./build-wrapper

echo "Install SonarCloud done."
