#ifndef _PARSER_H_
#define _PARSER_H_

/**
 *  Class responsible for loading in custom setup scripts and configuring the
 *  Universe appropriately.
 */
class Parser {
public:
    /**
     *  Loads the script file and configures the Universe. Consult the
     *  assignment PDF for the syntax of the scripts.
     */
    void loadFile(const char *filename);

private:

    const char* delims() {
        return "{}[], ";
    }

    double getDouble();
};

#endif
