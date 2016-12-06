#include <iostream>
#include <string>//for strings
#include <math.h>
#include <iomanip>//for setw
#include <fstream>//for files
#include <cstdlib>//for exit

using namespace std;

int const COURSE_MAX = 100;
int const REQ_COURSE_MAX = 100;

class Course
{
  public:
    Course();

    void getName(string& name);
    void getTime(string& time);
    void getNumber(string& number);
    void getGrade(char& grade);
    void getHours(int& hour);
    void getAvailability(bool& availability);

    void setName(string name);
    void setTime(string time);
    void setNumber(string number);
    void setGrade(char grade);
    void setHours(int hour);
    void setAvailability(bool availability);

    void print() const;

  private:
    string courseName;
    string courseTime;
    string courseNumber;
    char grade;
    int hours;
    bool availability;
};

Course::Course()
{
  courseName = "Programming foundations I";
  courseTime = "Fall 2015";
  courseNumber = "CSCE 2004";
  grade = 'A';
  hours = 4;
  availability = true;
}

//GET METHODS
void Course::getName(string& name)
{
  name = this->courseName;
}
void Course::getTime(string& time)
{
  time = this->courseTime;
}
void Course::getNumber(string& number)
{
  number = this->courseNumber;
}
void Course::getGrade(char& grade)
{
  grade = this->grade;
}
void Course::getHours(int& hour)
{
  hour = this->hours;
}
void Course::getAvailability(bool& availability)
{
  availability = this->availability;
}

//SET METHODS
void Course::setName(string name)
{
  this->courseName = name;
}
void Course::setTime(string time)
{
  this->courseTime = time;
}
void Course::setNumber(string number)
{
  this->courseNumber = number;
}
void Course::setGrade(char grade)
{
  this->grade = grade;
}
void Course::setHours(int hours)
{
  this->hours = hours;
}
void Course::setAvailability(bool availability)
{
  this->availability = availability;
}

void Course::print() const
{
  const char s = ' ';
  const int w = 40;

  cout << left << setw(w) << setfill(s) << this->courseName;
  cout << left << setw(w) << setfill(s) << this->courseTime;
  cout << left << setw(w) << setfill(s) << this->courseNumber;
  cout << left << setw(w) << setfill(s) << this->grade;
  cout << left << setw(w) << setfill(s) << this->hours;
  cout << left << setw(w) << setfill(s) << this->availability;
  cout << endl;
}

class Req
{
  public:
    Req();

    void getGroup(string& group);
    void getSubGroup(string& subGroup);
    void getHourSum(int& hourSum);
    void getCourses(Course& courses[]);
    void getStatus(bool& status);

    void setGroup(string group);
    void setSubGroup(string subGroup);
    void setHourSum(int hourSum);
    void setCourses(Course courses[]);
    void setStatus(bool status);

  private:
    string group;
    string subGroup;
    int hourSum;
    Course courses[REQ_COURSE_MAX];
    bool status;
};

Req::Req()
{
  group = "University Core";
  subGroup = "Default";
  hourSum = 0;
  courses[REQ_COURSE_MAX];
  status = false;
}
//get
void Req::getGroup(string& group)
{
  group = this->group;
}
void Req::getSubGroup(string& subGroup)
{
  subGroup = this->subGroup;
}
void Req::getHourSum(int& hourSum)
{
  hourSum = this->hourSum;
}
void Req::getCourses(Course courses[])
{
  courses = this->courses;
}
void Req::getStatus(bool& status)
{
  status = this->status;
}
//set
void Req::setGroup(string group)
{
  this->group = group;
}
void Req::setSubGroup(string subGroup)
{
  this->subGroup = subGroup;
}
void Req::setHourSum(int hourSum)
{
  this->hourSum = hourSum;
}
void Req::setCourses(Course courses[])
{
  this->courses = courses;
}
void Req::setStatus(bool status)
{
  this->status = status;
}

bool reading(const char filename[], int& n, int capacity, Course courseClasses[])
{
  ifstream file;
  file.open(filename);

  if(file.fail())
  {
    cout << "Failed to open file named: " << filename << endl;
    cout << "Error in reading the deafult file. Terminating..." << endl;
    exit(EXIT_FAILURE);
  }

  if(file.is_open())
  {
    //gets first line
    file >> n;
    file.ignore();

    if(n < capacity)
    {
      string tempName;
      string tempTime;
      string tempNumber;
      char tempGrade;
      int tempHours;

      for(int z = 0;z < n;z++)
      {
        cout << "Reading class " << z + 1 << endl;
        getline(file,tempName);
        getline(file,tempTime);
        getline(file,tempNumber);
        file >> tempGrade;
        file >> tempHours;
        file.ignore();

        //class
        courseClasses[z].setName(tempName);
        courseClasses[z].setTime(tempTime);
        courseClasses[z].setNumber(tempNumber);
        courseClasses[z].setGrade(tempGrade);
        courseClasses[z].setHours(tempHours);
      }
    }
    else
    {
      cout << "specified size on text file: " << filename << " is too large" << endl;
    }
  }

  file.close();

  return true;
}

bool writing(const char filename[], Course courseClasses[], int n)
{
  ofstream file;
  file.open(filename);

  if(file.fail())
  {
    cout << "Failed to recreate and open file named: " << filename << endl;
    exit(EXIT_FAILURE);
  }

  if(file.is_open())
  {
    file << n << endl;

    string tempName;
    string tempTime;
    string tempNumber;
    char tempGrade;
    int tempHours;

    for(int z = 0;z < n;z++)
    {
      courseClasses[z].getName(tempName);
      courseClasses[z].getTime(tempTime);
      courseClasses[z].getNumber(tempNumber);
      courseClasses[z].getGrade(tempGrade);
      courseClasses[z].getHours(tempHours);

      cout << "Writing class " << z + 1 << endl;
      file << tempName << endl;
      file << tempTime << endl;
      file << tempNumber << endl;
      file << tempGrade << endl;
      file << tempHours << endl;
    }
  }

  file.close();

  return true;
}

double gpa(int n, Course courseClasses[])
{
  char tempGrade;
  int tempHours;

  double tempGradePointsSum = 0;
  double tempCreditHoursSum = 0;
  double tempGradePointRep = -1;

  for(int z = 0; z < n; z++)
  {
    courseClasses[z].getGrade(tempGrade);
    courseClasses[z].getHours(tempHours);

    if(tempGrade == 'A')
    {
      tempGradePointRep = 4;
    }
    else if(tempGrade == 'B')
    {
      tempGradePointRep = 3;
    }
    else if(tempGrade == 'C')
    {
      tempGradePointRep = 2;
    }
    else if(tempGrade == 'D')
    {
      tempGradePointRep = 1;
    }
    else if(tempGrade == 'F')
    {
      tempGradePointRep = 0;
    }
    else
    {
      tempGradePointRep = -1;
    }

    if(tempGradePointRep >= 0)
    {
      tempGradePointsSum += (tempHours * tempGradePointRep);
      tempCreditHoursSum += tempHours;
    }
  }

  if(tempCreditHoursSum > 0)
    return (tempGradePointsSum / tempCreditHoursSum);
  else
    cout << "An error occured" << endl;
}

double semesterGpa(int n, Course courseClasses[], string semester)
{
  double tempGradePointsSum = 0;
  double tempCreditHoursSum = 0;
  double tempGradePointRep = -1;

  string tempTime;
  char tempGrade;
  int tempHours;

  for(int z = 0; z < n; z++)
  {
    courseClasses[z].getTime(tempTime);
    courseClasses[z].getGrade(tempGrade);
    courseClasses[z].getHours(tempHours);

    if(tempTime == semester)
    {
      if(tempGrade == 'A')
      {
        tempGradePointRep = 4;
      }
      else if(tempGrade == 'B')
      {
        tempGradePointRep = 3;
      }
      else if(tempGrade == 'C')
      {
        tempGradePointRep = 2;
      }
      else if(tempGrade == 'D')
      {
        tempGradePointRep = 1;
      }
      else if(tempGrade == 'F')
      {
        tempGradePointRep = 0;
      }
      else
      {
        tempGradePointRep = -1;
      }

      if(tempGradePointRep >= 0)
      {
        tempGradePointsSum += (tempHours * tempGradePointRep);
        tempCreditHoursSum += tempHours;
      }
    }
  }

  if(tempCreditHoursSum > 0)
    return (tempGradePointsSum / tempCreditHoursSum);
  else
    cout << "An error occured" << endl;
}

int DRule(int n, Course courseClasses[])
{
  char tempGrade;
  int tempHours;

  int calculation = 0;

  for(int z = 0;z < n;z++)
  {
    courseClasses[z].getGrade(tempGrade);
    courseClasses[z].getHours(tempHours);

    if(tempGrade == 'D')
    {
      calculation += tempHours;
    }
  }

  return calculation;
}

void print(int n, Course courseClasses[])
{
  cout << endl;

  cout << "Displaying (" << n << " of " << n << ") courses." << endl << endl;

  const char s = ' ';
  const int w = 40;

  cout << left << setw(w) << setfill(s) << "Course Name";
  cout << left << setw(w) << setfill(s) << "Semester";
  cout << left << setw(w) << setfill(s) << "Course Number";
  cout << left << setw(w) << setfill(s) << "Grade";
  cout << left << setw(w) << setfill(s) << "Hour";
  cout << endl << endl;

  string tempName;
  string tempTime;
  string tempNumber;
  char tempGrade;
  int tempHours;

  //lists all courses
  for(int z = 0;z<n;z++)
  {
    courseClasses[z].getName(tempName);
    courseClasses[z].getTime(tempTime);
    courseClasses[z].getNumber(tempNumber);
    courseClasses[z].getGrade(tempGrade);
    courseClasses[z].getHours(tempHours);

    cout << left << setw(w) << setfill(s) << tempName;
    cout << left << setw(w) << setfill(s) << tempTime;
    cout << left << setw(w) << setfill(s) << tempNumber;
    cout << left << setw(w) << setfill(s) << tempGrade;
    cout << left << setw(w) << setfill(s) << tempHours;
    cout << endl;
  }

  cout << endl;
}

void getCourse(int n, Course& courseClass)
{
  string tempName;
  string tempTime;
  string tempNumber;
  char tempGrade;
  int tempHours;

  //name
  cout << "Enter the course name (e.g. Programming Foundations I) for class number " << n << endl;
  getline(cin,tempName);

  while(tempName == "")
  {
    cout << "Invalid input. Please try again." << endl;
    getline(cin,tempName);
  }
  //time
  cout << "Enter the semester (e.g. Spring 2016) for class number " << n << endl;
  getline(cin,tempTime);

  while(tempTime == "")
  {
    cout << "Invalid input. Please try again." << endl;
    getline(cin,tempTime);
  }
  //number
  cout << "Enter the course number (e.g. CSCE 2004) for class number " << n << endl;
  getline(cin,tempNumber);

  while(tempNumber == "")
  {
    cout << "Invalid input. Please try again." << endl;
    getline(cin,tempNumber);
  }
  //grade
  string tempString = "";
  while(tempString == "")
  {
    cout << "Enter the grade (A,B,C,D,F,W,I) for class number " << n << endl;
    getline(cin,tempString);

    if(tempString == "A" || tempString == "a")
    {
      tempGrade = 'A';
    }
    else if(tempString == "B" || tempString == "b")
    {
      tempGrade = 'B';
    }
    else if(tempString == "C" || tempString == "c")
    {
      tempGrade = 'C';
    }
    else if(tempString == "D" || tempString == "d")
    {
      tempGrade = 'D';
    }
    else if(tempString == "F" || tempString == "f")
    {
      tempGrade = 'F';
    }
    else if(tempString == "W" || tempString == "w")
    {
      tempGrade = 'W';
    }
    else if(tempString == "I" || tempString == "i")
    {
      tempGrade = 'I';
    }
    else
    {
      tempString = "";
      cout << "Invalid user input, please try again" << endl;
    }
  }
  //number
  cout << "Enter the course hours (1 ... 5) for class number " << n << endl;
  cin >> tempHours;

  while(tempHours < 1 && tempHours > 5)
  {
    cout << "Invalid user input, please try again." << endl;
    cout << "Enter the course hours (1 ... 5) for class number " << n << endl;
    cin >> tempHours;
  }

  cin.ignore();

  courseClass.setName(tempName);
  courseClass.setTime(tempTime);
  courseClass.setNumber(tempNumber);
  courseClass.setGrade(tempGrade);
  courseClass.setHours(tempHours);
}

char menu()
{
  string tempString;

  //return overrides while loop
  while(true)
  {
    cout << "Please enter the character next to the choice you wish to pick." << endl;
    cout << "Here are your options:" << endl;
    cout << "A(a) . Compute the GPA of all courses" << endl;
    cout << "B(b) . List all courses" << endl;
    cout << "C(c) . Compute the total credit hours of the courses with grade D" << endl;
    cout << "D(d) . Compute the GPA for a particular semester" << endl;
    cout << "E(e) . Add another course to the course list" << endl;
    cout << "F(f) . Delete a course from the course list" << endl;
    cout << "Q(q) . Quit the program" << endl;
    cout << "Please choose one of the above" << endl;

    getline(cin,tempString);

    if(tempString == "A" || tempString == "a")
    {
      return 'A';
    }
    else if(tempString == "B" || tempString == "b")
    {
      return 'B';
    }
    else if(tempString == "C" || tempString == "c")
    {
      return 'C';
    }
    else if(tempString == "D" || tempString == "d")
    {
      return 'D';
    }
    else if(tempString == "E" || tempString == "e")
    {
      return 'E';
    }
    else if(tempString == "F" || tempString == "f")
    {
      return 'F';
    }
    else if(tempString == "Q" || tempString == "q")
    {
      return 'Q';
    }
    else
    {
      cout << "Invalid selection. Please try again." << endl;
    }
  }
}

int main ()
{
  string selectedFilename;

  int courses = 0;
  string mode = "";
  string tempString = "";

  //init all vars
  //initalizes all array vars based on defined validated input above
  Course courseClasses[COURSE_MAX];

  cout << "Welcome to PFI course management system v1" << endl;
  cout << "Would you like to read the courses taken from a file?" << endl;
  cout << "Please enter y for yes and n for no" << endl;
  getline(cin, mode);

  while(mode != "y" && mode != "n")
  {
    cout << "The character entered is " << mode << ". That is not y or n";
    cout << "Would you like to read the courses taken from a file?" << endl;
    cout << "Please enter y for yes and n for no" << endl;
    getline(cin, mode);
  }

  if(mode == "y")
  {
    string stock = "";

    cout << "Would you like to use the default file?" << endl;
    cout << "Please enter y for yes and n for no" << endl;
    getline(cin, stock);

    while(stock != "y" && stock != "n")
    {
      cout << "The character entered is " << stock << ". That is not y or n";
      cout << "Would you like to use the default file?" << endl;
      cout << "Please enter y for yes and n for no" << endl;
      getline(cin, stock);
    }

    if(mode == "y")
    {
      reading("courses.txt", courses, COURSE_MAX, courseClasses);
    }
    else
    {
      cout << "Enter your file name" << endl;
      getline(cin, selectedFilename);

      while(selectedFilename == "")
      {
        cout << "Invalid filename. Please try again." << endl;
        getline(cin, selectedFilename);
      }

      reading(selectedFilename.c_str(), courses, COURSE_MAX, courseClasses);
    }
  }

  if(courses == 0)
  {
    cout << "Interactive mode was selected." << endl;
    cout << "Enter the number of classes for the system [1," << COURSE_MAX << "]" << endl;
    cin >> courses;

    while(courses <= 0 && courses >= COURSE_MAX)
    {
      cout << "The supplied input was not within specified bounds. Please try again." << endl;
      cin >> courses;
    }

    cin.ignore();

    for(int step = 0;step < courses;step++)
    {
      //comeback
      getCourse(courses, courseClasses[step]);
    }
  }

  cout << "Welcome to the interactive menu-driven part of the GPA and Course storage program." << endl;

  while(true)
  {
    char menuSelector = menu();

    if(menuSelector == 'A')
    {
      cout << "Congratulations, your GPA was " << gpa(courses, courseClasses) << endl;
    }
    else if(menuSelector == 'B')
    {
      print(courses, courseClasses);
    }
    else if(menuSelector == 'C')
    {
      cout << "Total hours with D grades are " << DRule(courses, courseClasses) << endl;
    }
    else if(menuSelector == 'D')
    {
      double tempGPA = 0;
      string selectedSemester = "";
      int semesterIndex;

      cout << "Please input desired semester for calculation" << endl;
      getline(cin,selectedSemester);

      double tempClasses = 0;

      string tempTime;

      while(tempClasses == 0)
      {
        for(int z = 0; z<courses;z++)
        {
          courseClasses[z].getTime(tempTime);

          if(tempTime == selectedSemester)
          {
            tempClasses++;
          }
        }
        if(tempClasses == 0)
        {
          cout << "Desired semester: " << selectedSemester << " was not found. Please try again." << endl;
          cout << "Please input desired semester for calculation" << endl;
          getline(cin,selectedSemester);
        }
      }

      cout << "Congratulations, your GPA was " << semesterGpa(courses, courseClasses, selectedSemester) << " in " << selectedSemester << endl;
    }
    else if(menuSelector == 'E')
    {
      if(courses + 1 < COURSE_MAX)
      {
        courses++;

        getCourse(courses, courseClasses[courses - 1]);
      }
      else
      {
        cout << "Unable to add more than " << COURSE_MAX << " classes" << endl;
      }
    }
    else if(menuSelector == 'F')
    {
      if(courses - 1 >= 0)
      {
        int selection = 0;
        cout << "Select from 1 to " << courses << " for the course to be deleted" << endl;
        cin >> selection;
        cin.ignore();

        while(selection < 0 && selection > courses)
        {
          cout << "Invalid selection. Please try again" << endl;
          cin >> selection;
          cin.ignore();
        }

        string tempName;
        string tempTime;
        string tempNumber;
        char tempGrade;
        int tempHours;

        //move elemnts left 1
        for(int z = selection;z < courses;z++)
        {
          //name
          courseClasses[z].getName(tempName);
          courseClasses[z - 1].setName(tempName);
          //time
          courseClasses[z].getTime(tempTime);
          courseClasses[z - 1].setTime(tempTime);
          //number
          courseClasses[z].getNumber(tempNumber);
          courseClasses[z - 1].setNumber(tempNumber);
          //grade
          courseClasses[z].getGrade(tempGrade);
          courseClasses[z - 1].setGrade(tempGrade);
          //hours
          courseClasses[z].getHours(tempHours);
          courseClasses[z - 1].setHours(tempHours);
        }

        courses--;
      }
      else
      {
        cout << "There are not any courses to remove" << endl;
      }
    }
    else if(menuSelector == 'G')
    {
      /*
      ifstream file;
      file.open(filename);

      if(file.fail())
      {
        cout << "Failed to open file named: " << filename << endl;
        cout << "Error in reading the deafult file. Terminating..." << endl;
        exit(EXIT_FAILURE);
      }

      if(file.is_open())
      {
        //gets first line
        file >> n;
        file.ignore();

        if(n < capacity)
        {
          string tempName;
          string tempTime;
          string tempNumber;
          char tempGrade;
          int tempHours;

          for(int z = 0;z < n;z++)
          {
            cout << "Reading class " << z + 1 << endl;
            getline(file,tempName);
            getline(file,tempTime);
            getline(file,tempNumber);
            file >> tempGrade;
            file >> tempHours;
            file.ignore();

            //class
            courseClasses[z].setName(tempName);
            courseClasses[z].setTime(tempTime);
            courseClasses[z].setNumber(tempNumber);
            courseClasses[z].setGrade(tempGrade);
            courseClasses[z].setHours(tempHours);
          }
        }
        else
        {
          cout << "specified size on text file: " << filename << " is too large" << endl;
        }
      }

      file.close();
      */

      //logic
        //get file
        //create array of req obj
        //req obj =
          //group
          //subgroup
          //credit sum
          //class list array
        //iterate through all classes and check if all classes
        //in class list array AND/OR totaling to the credit sum.
        //and if the course has availability = true, then:
          //set availability of course = false; set status of req obj = true;(passed)

      //on empty line, iterate new loop and repeat logic above

      //user interface
        //print group
          //print all subgroups with goup above with status (true/false)
    }
    else if(menuSelector == 'Q')
    {
      if(selectedFilename == "")
      {
        writing("courses.txt", courseClasses, courses);
      }
      else
      {
        writing(selectedFilename.c_str(), courseClasses, courses);
      }
      //"escapes all logic"
      return 0;
    }
  }
}
