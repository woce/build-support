// @@@LICENSE
//
//      Copyright (c) 2010-2012 Hewlett-Packard Development Company, L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// LICENSE@@@

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#define PDK_TEMPLATE_PATH "/usr/palm/ls2/templates/PDK"
#define TRITON_TEMPLATE_PATH "/usr/palm/ls2/templates/Triton"
#define LS2_ROLE_PATH "/var/palm/ls2/roles"
#define TRITON_EXE_PATH "js"

using namespace std;

void pdkGenerateRole(string id, string executablePath);
void roleGenerate(string templatePath, string destinationPath, string id, string executablePath);
void tritonGenerateRole(string id);
