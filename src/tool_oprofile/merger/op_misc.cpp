//
// Created by Jean Pourroy on 21/07/2017.
//

#include <assert.h>
#include "op_misc.h"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

#include "../../common/AnyOption/anyoption.h"

ui64 stoullhexa(string str) {
    ui64 add = 0;
    for (int i = 0;; i++) {
        char c = str[i];
        if ((c >= '0') and (c <= '9')) {
            add *= 16;
            add += (c - '0');
            continue;
        }
        if ((c >= 'a') and (c <= 'f')) {
            add *= 16;
            add += (c - 'a' + 10);
            continue;
        }
        if ((c >= 'A') and (c <= 'F')) {
            add *= 16;
            add += (c - 'A' + 10);
            continue;
        }
        break;
    }
    return (add);
}

const vector<string> my_split(const string &s, const char &c) {
    string buff{""};
    vector<string> v;

    for (auto n:s) {
        if (n != c) buff += n;
        else if (n == c && buff != "") {
            v.push_back(buff);
            buff = "";
        }
    }
    if (buff != "") v.push_back(buff);
    return v;
}


//https://stackoverflow.com/questions/3613284/c-stdstring-to-boolean
bool to_bool(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::istringstream is(str);
    bool b;
    is >> std::boolalpha >> b;
    return b;
}


void parse_argument(int argc, char *argv[], AnyOption *opt) {

    /* 1. CREATE AN OBJECT */
    /* 2. SET PREFERENCES  */
    // opt->noPOSIX(); /* do not check for POSIX style character options */
    // opt->setVerbose(); /* print warnings about unknown options */
    opt->autoUsagePrint(true); /* print usage for bad options */

    /* 3. SET THE USAGE/HELP   */
    opt->addUsage("usage: ./merger --object <path> --profile <path> [--sum {true,false}] [--ipc {true,false}]");
    opt->addUsage("   -h  --help                Prints this help ");
    opt->addUsage("   -o  --object  <path>      Objdump  output file");
    opt->addUsage("   -p  --profile <path>      Oprofile output file");
    opt->addUsage("   -s  --sum  {true,false}   Display sum section");
    opt->addUsage("   -i  --ipc  {true,false}   Display IPC");

    /* 4. SET THE OPTION STRINGS/CHARACTERS */

    /* by default all  options  will be checked on the command line and from
     * option/resource file */
    opt->setFlag(
            "help",
            'h'); /* a flag (takes no argument), supporting long and short form */
    opt->setOption(
            "sum",
            's'); /* a flag (takes no argument), supporting long and short form */
    opt->setOption(
            "ipc",
            'i'); /* a flag (takes no argument), supporting long and short form */
    opt->setOption(
            "object",
            'o'); /* an option (takes an argument), supporting long and short form */
    opt->setOption(
            "profile",
            'p'); /* an option (takes an argument), supporting long and short form */


    /* 5. PROCESS THE COMMANDLINE AND RESOURCE FILE */

    /* go through the command line and get the options  */
    opt->processCommandArgs(argc, argv);

    if (!opt->hasOptions()) { /* print usage if no options */
        opt->printUsage();
        delete opt;
        return;
    }

    /* 6. GET THE VALUES */
    if (opt->getFlag("help") || opt->getFlag('h')) {
        opt->printUsage();
        exit(0);
    }


    cout << " --------------- CONFIGURATION -------------\n";
    if (opt->getValue('o') != NULL || opt->getValue("object") != NULL)
        cout << "object        " << opt->getValue('o') << endl;
    if (opt->getValue('p') != NULL || opt->getValue("profile") != NULL)
        cout << "profile       " << opt->getValue('p') << endl;

    if (opt->getValue("sum") == NULL && opt->getValue('s') == NULL) {
        opt->setValue ('s',  (char *)("false"));
    }
    cout << "Display sum   " << opt->getValue('s') << endl ;

    if (opt->getValue("ipc") == NULL && opt->getValue('i') == NULL) {
        opt->setValue ("ipc",  (char *)("false"));
    }
    cout << "Display ipc   " << opt->getValue('i') << endl ;

    /* 7. GET THE ACTUAL ARGUMENTS AFTER THE OPTIONS */
    for (int i = 0; i < opt->getArgc(); i++) {
        cout << "arg = " << opt->getArgv(i) << endl;
    }

    if ((opt->getValue('o') == NULL && opt->getValue("object") == NULL) ||
        (opt->getValue('p') == NULL && opt->getValue("profile") == NULL)) {
        cerr << "Need at least 2 arguments\n";
        opt->printUsage();
        exit(-1);
    }

    cout << " -------------------------------------------\n";

    /* 8. DONE */
}

