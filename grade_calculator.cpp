// These headers define some of the classes and functions we need
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

// ONLY MAKE CHANGES WHERE THERE IS A TODO

// These using declarations let us refer to things more simply
// e.g. instead of "std::cin" we can just write "cin" 
using std::cin, std::cout, std::endl;
using std::string, std::getline;

// These methods are defined below the main function

// print instructions for inputting grades
void print_instructions();

// pretty print a summary of the grades 
void print_results(double exam_average,
                   double hw_average,
                   double lw_average,
                   double engagement,
                   double weighted_total,
                   char final_letter_grade);

// YOU ARE NOT EXPECTED TO UNDERSTAND THIS ONE... YET
// extract the category and score from the line
// and store the values in the provided variables
// if line := "exam 95", then category := "exam" and score := 95
// if the line is invalid, then category := "ignore"
void get_category_and_score(const string& line,
                            string* category,
                            double* score);

int main() {
    print_instructions();

    // ONLY MAKE CHANGES WHERE THERE IS A TODO
    
    // TODO(student): declare and initialize variables that you want
    double examCt = 0;
    double examSum = 0;
    double finExam = 0;
    double hwCt = 0;
    double hwSum = 0;
    double lwCt = 0;
    double lwSum = 0;
    double engageSum = 0;
    double engageCt = 0;
    string line;

    // read one line from standard input (discards the ending newline character)
    getline(cin, line);
    // read lines until an empty line is read
    while (!line.empty()) {
        string category;
        double score;
        get_category_and_score(line, &category, &score);

        // process the grade entry
        if (category == "exam") {
            // TODO(student): process exam score
                examSum += score;
                examCt += 1;
        } else if (category == "final-exam") {
            // TODO(student): process final score
            finExam = score;
        } else if (category == "hw") {
            // TODO(student): process hw score
            hwSum += score;
            hwCt += 1;
        } else if (category == "lw") {
            // TODO(student): process lw score
            if (score > 1) {
                score = 1;
            }
            lwSum += score;
            lwCt += 1;
        } else if (category == "engagement") {
            // TODO(student): process engagement score
            engageSum += score;
            engageCt = 1;
        } else {
            cout << "ignored invalid input" << endl;
        }

        // get the next line from standard input
        getline(cin, line);
    }

    // TODO(student): compute component averages
    double nofinal_average = examSum/examCt;
    if (nofinal_average < 60) {
        examCt += 1;
    }
    double exam_average = examSum/examCt;
    double hw_average = hwSum/hwCt;
    double lw_average = (lwSum/lwCt)*100;
    double engagement = engageSum;
    if (engagement >= 100) {
        engagement = 100;
    }
    if (finExam != 0) {
        exam_average = (examSum + finExam)/(examCt + 1);
    }
    if (examCt == 0 && examSum == 0 && finExam == 0) {
        exam_average = 0;
    }
    if (finExam > nofinal_average) {
        exam_average = finExam;
    }
    if (hwCt == 0) {
        hw_average = 0;
    }
    if (lwCt == 0) {
        lw_average = 0;
    }
    if (engageCt < 1) {
        engagement = 0;
    } 

    // TODO(student): compute weighted total of components
    double weighted_total = exam_average*.4+hw_average*.4+lw_average*.1+engagement*.1;

    // TODO(student): compute final letter grade
    char final_letter_grade;
    if (weighted_total >= 90) {
        final_letter_grade = 'A';
    } else if (weighted_total >= 80) {
        final_letter_grade = 'B';
    } else if (weighted_total >= 70) {
        final_letter_grade = 'C';
    } else if (weighted_total >= 60) {
        final_letter_grade = 'D';
    } else {
        final_letter_grade = 'F';
    }

    print_results(
        exam_average, hw_average, lw_average, engagement,
        weighted_total, final_letter_grade);
}

// These methods are already implemented for you
// You should not need to modify them

void print_instructions() {
    cout << "enter grades as <category> <score>" << endl;
    cout << "  <category> := exam | final-exam | hw | lw | engagement" << endl;
    cout << "     <score> := numeric value" << endl;
    cout << "enter an empty line to end input" << endl;
}

void get_category_and_score(
    const string& line,
    string* category,
    double* score) {
    // turn the string into an input stream
    std::istringstream sin(line);

    // read the category (as string) and score (as double) from the stream
    sin >> *category;
    sin >> *score;

    if (sin.fail()) {
        // the stream is in a fail state (something went wrong)
        // clear the flags
        sin.clear();
        // clear the stream buffer (throw away whatever garbage is in there)
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // signal that the line was invalid
        *category = "ignore";
    }
}

void print_results(
    double exam_average,
    double hw_average,
    double lw_average,
    double engagement,
    double weighted_total,
    char final_letter_grade) {
    cout << "summary:" << endl;
    cout << "      exam average: " << exam_average << endl;
    cout << "        hw average: " << hw_average << endl;
    cout << "        lw average: " << lw_average << endl;
    cout << "        engagement: " << engagement << endl;
    cout << "    ---------------" << endl;

    cout << "    weighted total: " << weighted_total << endl;

    cout << "final letter grade: " << final_letter_grade << endl;
}
