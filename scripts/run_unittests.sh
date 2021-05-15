#!/bin/bash

source src/esysrepo/scripts/start_ssh_agent

build/cmake/bin/esysrepo_t --logger=HRF,test_suite,stdout:JUNIT,all,report.junit