#include <bits/stdc++.h>
using namespace std;
class Book{     //here we have assumed ISBN is a int we can easily change it if we want
    public:
    string Title;
    string Author;
    string ISBN;
    string Publication;
    int available;
    pair<string,string> owner;
    time_t time_of_issue;
    bool Book_request(string user){   //this function will be used to request a book
        if(available==1){       // available=1 means book is available
            cout<<"The book have been issued to you please take keep it with care\n";
            available=0;
            time_of_issue=time(0);  //time_of_issue will be used to calculate the time of issue
            return true;
        }
        else{                   //available=0 means book is not available
            cout<<"Sorry but the book is not available you can try later Thank you\n";
            return false;
        }
    }
    int show_duedate(string user){
        if(user=="student"){
            return 30-ceil(difftime(time(0),time_of_issue)/(24*60*60));
        }
        else if(user=="professor"){
            return 60-ceil(difftime(time(0),time_of_issue)/(24*60*60));
        }
        return 0;
    }
    Book(string Title1,string Author1,string ISBN1,string Publication1)// constructor
    {
        Title=Title1;
        Author=Author1;
        ISBN=ISBN1;
        Publication=Publication1;
        available=1;
    }
};
class Book_db{  //store all the books in the library
    public:
    vector<Book>list_of_books;
    void add_book(Book book){
        list_of_books.push_back(book);
        cout<<"Book added successfully\n";
    }
    Book remove_book(string ISBN){
        int f=0;
        Book r("","","0","");
        for(auto it=list_of_books.begin();it!=list_of_books.end();it++){
            Book b=*it;
            if(b.ISBN==ISBN){
               r=b;
               f=1;
               list_of_books.erase(it);
               break;
            }
        }
        if(f==0){
            cout<<"Book not found\n";
        }
        else{
            cout<<"This Book has been removed\n";
            cout<<"Title: "<<r.Title<<"\n";
            cout<<"Author: "<<r.Author<<"\n";
            cout<<"ISBN: "<<r.ISBN<<"\n";
            cout<<"Publication: "<<r.Publication<<"\n";
            cout<<"\n";
        }
        return r;
    }
    void search_book_by_Title(string Title){
        int f=0;
        for(auto it=list_of_books.begin();it!=list_of_books.end();it++){
            Book b=*it;
            if(b.Title==Title){
                f=1;
                cout<<"Title: "<<b.Title<<endl;
                cout<<"Author: "<<b.Author<<endl;
                cout<<"ISBN: "<<b.ISBN<<endl;
                cout<<"Publication: "<<b.Publication<<endl;
                string temp=b.available?"available":"not available";
                cout<<"Book Status: "<<temp<<"\n";
                cout<<"\n";
                break;
            }
        }
        if(f==1){
        }
        else{
            cout<<"Sorry to say but the book is not available\n";
        }
    }
    void search_book_by_ISBN(string ISBN){
        int f=0;
        for(auto it=list_of_books.begin();it!=list_of_books.end();it++){
            Book b=*it;
            if(b.ISBN==ISBN){
                f=1;
                cout<<"Yes we have this book\n";
                cout<<"Title: "<<b.Title<<endl;
                cout<<"Author: "<<b.Author<<endl;
                cout<<"ISBN: "<<b.ISBN<<endl;
                cout<<"Publication: "<<b.Publication<<endl;
                string temp=b.available?"available":"not available";
                cout<<"Book Status: "<<temp<<"\n";
                cout<<"\n";
                break;
            }
        }
        if(f==1){
        }
        else{
            cout<<"Sorry to say but the book is not available\n";
        }
    }
    Book update_book(string ISBN){   //this function will be used to update the book we have allowed only update by title as two books can have similar title
        int f=0;
        Book b("0","0","0","0");
        auto it=list_of_books.begin();
        for(it=list_of_books.begin();it!=list_of_books.end();it++){
            b=*it;
            if(b.ISBN==ISBN){
                cout<<"Enter the new Title\n";
                string Title;
                getline(cin,Title);
                it->Title=Title;
                cout<<"Enter the new Author\n";
                string Author;
                getline(cin,Author);
                it->Author=Author;
                cout<<"Enter the new Publication\n";
                string Publication;
                getline(cin,Publication);
                it->Publication=Publication;
                f=1;
                break;
            }
         }
         if(f==0){
            cout<<"Book not found\n";
         }
         else{
            cout<<"Book updated\n";
            b=*it;
            return b;
         }
        return b;
    }
    void list_all_books(){
        if(this->list_of_books.size()==0){
            cout<<"No book in library\n";
            return;
        }
        cout<<"The list of all the books is as follows\n\n";
        for(auto it:this->list_of_books){
            Book b=it;
            cout<<"Book Name: "<<b.Title<<"\n";
            cout<<"Book Author: "<<b.Author<<"\n";
            cout<<"Book Publisher: "<<b.Publication<<"\n";
            string temp=b.available?"availble":"not available";
            cout<<"Book Status: "<<temp<<"\n";
            cout<<"Book ISBN: "<<b.ISBN<<"\n";
            cout<<"\n";
        }
        cout<<"\n";
    }
};
class User{     //this will be the parent class for student,professor and librarian
    public:
    vector<Book>list_of_book;   //this is the list of book with user
    string Name;
    string id;   //this will be a auto generated unique id on the addition of user
    string Password;
    long long int fine;
    void Calculate_fine(){      //here we calculate the fine
        int f=0;
        fine=0;
        for(auto book:list_of_book){
            double jhc=difftime(time(0),book.time_of_issue)/(24*60*60);
            if(jhc>30){
                fine=fine+ceil(jhc-30)*2;
            }
        }
        cout<<"The fine is "<<fine<<"\n";
    }
    void clear_fine(){  //this function will clear the fine and we reset the fine to 0 and time of issue for the fined book to 
        cout<<"All the books which have fine on it date of issue will be set to today after you pay all the fine and if you want to submit then go to submit option\n";
        Calculate_fine();//we first calculate the fine
        if(fine!=0){
            cout<<"Please pay "<<fine<<"\n";
        }
        else{
            cout<<"You have no fine\n";
            return;
        }
        int y=0;
        for(auto it:list_of_book){
            double jhc=difftime(time(0),it.time_of_issue)/(24*60*60);
            if(jhc>30){
                list_of_book[y].time_of_issue=time(0);
            }
            y++;
        }
        cout<<"Thank you \n";
        fine=0;
    }
};
class Student:public User{  //derived class from user
    public:
    void issue_book(Book_db &book_db){
        cout<<"Enter the ISBN of the book you want to issue\n";
        string ISBN;
        getline(cin,ISBN);
        int f=0;
        for(auto book:list_of_book){        //we search whether we already does have this book in our list
            if(book.ISBN==ISBN){
                f=1;
                break;
            }
        }
        if(list_of_book.size()==5){         //check for max book for student
            cout<<"You have already issued 5 books\n";
            return;
        }
        if(f==1){
            cout<<"You have already issued this book\n";
        }
        else{
            int y=0;
            for(int j=0;j<book_db.list_of_books.size();j++){
                Book book=book_db.list_of_books[j];
                if(list_of_book.size()<5&&book.ISBN==ISBN){
                    y=1;
                    if(book.Book_request("student")){   //set the owner of the book to student
                        book_db.list_of_books[j].owner.first=Name;
                        book_db.list_of_books[j].owner.second=id;
                        book_db.list_of_books[j].available=0;
                        book_db.list_of_books[j].time_of_issue=time(0);
                         time_t x=time(0);              // set the time of issue
                        char* dt = ctime(&x);
                        cout<<"The time of issue is: ";
                        cout<<dt;
                        list_of_book.push_back(book_db.list_of_books[j]);
                        cout<<"You have issued the book: ";
                        cout<<book_db.list_of_books[j].Title<<"\n";
                    }
                    break;
                }
            }
            if(y==0){
                cout<<"Book not found\n";
            }
        }
    }
    void submit_book(Book_db &book_db){
        Calculate_fine();           //first we calculate the fine
        if(fine>0){
            cout<<"Please pay the fine first\n";    //if fine is greater than 0 then we cannot submit the bookand you have to pay fine first
            return;
        }
        cout<<"Enter the ISBN of the book you want to submit\n";
        string ISBN;
        getline(cin,ISBN);
        int f=0;
        auto it = list_of_book.begin();
        for(auto book:list_of_book){
            if(book.ISBN==ISBN){
                f=1;
                (this->list_of_book).erase(it);
                cout<<list_of_book.size();
                int y=0;
                for(int j=0;j<book_db.list_of_books.size();j++){
                    Book b=book_db.list_of_books[j];
                    if(b.ISBN==ISBN){
                        book_db.list_of_books[y].owner.first="None";
                        book_db.list_of_books[y].owner.second="0";
                        book_db.list_of_books[y].available=1;
                        time_t x=time(0);
                        char* dt = ctime(&x);
                        cout<<dt<<"\n";
                        break;
                    }
                    y++;
                }
                it++;
                break;
            }
        }
        if(f==0){
            cout<<"You have not issued this book\n";
        }
        else{
            cout<<"Your book has been submitted\n";
        }
    }
    Student(string name,string ID,string password){  //constructor
        Name=name;
        id=ID;
        Password=password;
    }
};
class Professor:public User{
    public:
    void issue_book(Book_db &book_db){
        cout<<"Enter the ISBN of the book you want to issue\n";
        string ISBN;
        getline(cin,ISBN);
        int f=0;
        for(auto book:list_of_book){
            if(book.ISBN==ISBN){
                f=1;
                break;
            }
        }
        if(f==1){
            cout<<"You have already issued this book\n";
        }
        else{
            int y=0;
            for(int j=0;j<book_db.list_of_books.size();j++){
                Book book=book_db.list_of_books[j];
                if(book.ISBN==ISBN){
                    y=1;
                    if(book.Book_request("professor")){
                        book_db.list_of_books[j].owner.first=Name;
                        book_db.list_of_books[j].owner.second=id;
                        book_db.list_of_books[j].available=0;
                        book_db.list_of_books[j].time_of_issue=time(0);
                        time_t x=time(0);              // set the time of issue
                        char* dt = ctime(&x);
                        cout<<"The time of issue is: ";
                        cout<<dt;                       
                        cout<<"You have issued the book: ";
                        cout<<book_db.list_of_books[j].Title<<"\n";
                        list_of_book.push_back(book_db.list_of_books[j]);
                    }
                    break;
                }
            }
            if(y==0){
                cout<<"Book not found\n";
            }
        }
    }
    void submit_book(Book_db &book_db){
        Calculate_fine();
        if(fine>0){
            cout<<"Please pay the fine first\n";
            return;
        }
        cout<<"Enter the ISBN of the book you want to submit\n";
        string ISBN;
        getline(cin,ISBN);
        int f=0;
        auto it = list_of_book.begin();
        for(auto book:list_of_book){
            if(book.ISBN==ISBN){
                f=1;
                (this->list_of_book).erase(it);
                int y=0;
                for(int j=0;j<book_db.list_of_books.size();j++){
                    Book b=book_db.list_of_books[j];
                    if(b.ISBN==ISBN){
                        book_db.list_of_books[y].owner.first="None";
                        book_db.list_of_books[y].owner.second="0";
                        book_db.list_of_books[y].available=1;
                        break;
                    }
                    y++;
                }
                it++;
                break;
            }
        }
        if(f==0){
            cout<<"You have not issued this book\n";
        }
        else{
            cout<<"Your book has been submitted\n";
        }
    }
    Professor(string name,string ID,string password){
        Name=name;
        id=ID;
        Password=password;
    }
};
class Librarian:public User{
    public:
    Librarian(string name,string ID,string password){//constructor
        Name=name;
        id=ID;
        Password=password;
    }
};
class User_db{
    public:
    vector<Professor>professor_list;
    vector<Student>student_list;
    vector<Librarian>librarian_list;
    void list_all_books_of_user(string id){      //list all the books of a user
        int f=0;
        for(auto it:student_list){
            Student s=it;
            if(s.id==id){
                cout<<s.Name<<"\n";
                f=1;
                if(s.list_of_book.size()==0){           //if no books with the user 
                    cout<<"You have not issued any book\n";
                    break;
                }
                cout<<"Books issued: \n";
                for(auto book:s.list_of_book){
                    Book b=book;
                    cout<<"Book Name: "<<b.Title<<"\n";
                    cout<<"Book Author: "<<b.Author<<"\n";
                    cout<<"Book Publisher: "<<b.Publication<<"\n";
                    cout<<"Book due day before submission: "<<book.show_duedate("student")<<"\n";   //show the number of days before fine
                    cout<<"\n";
                }
                break;
            }
            cout<<"\n";
        }
        if(f==0)
        for(auto it:professor_list){        //for printing all books with professor
            Professor p=it;
            if(p.id==id){
                f=1;
                cout<<p.Name<<"\n";
                if(p.list_of_book.size()==0){
                    cout<<"You have not issued any book\n";
                    break;
                }
                cout<<"Books issued\n";
                for(auto book:p.list_of_book){
                    Book b=book;
                    cout<<"Book Name: "<<b.Title<<"\n";
                    cout<<"Book Author: "<<b.Author<<"\n";
                    cout<<"Book Publisher: "<<b.Publication<<"\n";
                    cout<<"Book due day before submission: "<<book.show_duedate("professor")<<"\n";
                    cout<<"\n";
                }
                break;
            }
        }
        if(f==0){
            cout<<"No such user exist\n";
        }
        cout<<"\n";
    }
    void add_student(){                            //add student to the database        
        cout<<"Enter the name of the student\n";
        string name;
        getline(cin,name);
        cout<<"Enter the ID of the student\n";
        string id;
        getline(cin,id);
        cout<<"Enter the password of the student\n";
        string password;
        getline(cin,password);
        Student s(name,id,password);
        this->student_list.push_back(s);
        cout<<"User has been added successfully\n";
    }
    void add_professor(){                           //add professor to the database
        cout<<"Enter the name of the professor\n";
        string name;
        getline(cin,name);
        string ID;
        cout<<"Enter the ID of the professor\n";
        getline(cin,ID);
        cout<<"Enter the password of the professor\n";
        string password;
        getline(cin,password);
        Professor p(name,ID,password);
        this->professor_list.push_back(p);
        cout<<"User has been added successfully\n";
    }
    void add_librarian(){                           //add librarian to the database
        cout<<"Enter the name of the librarian\n";
        string name;
        getline(cin,name);
        string ID;
        cout<<"Enter the ID of the librarian\n";
        getline(cin,ID);
        cout<<"Enter the password of the librarian\n";
        string password;
        getline(cin,password);
        Librarian l(name,ID,password);
        this->librarian_list.push_back(l);
        cout<<"User has been added successfully\n";
    }
    void update_student(){                          //update student details
        cout<<"Enter the id of the user you want to update\n";
        string id;
        getline(cin,id);
        auto it=this->student_list.begin();
        for(it=this->student_list.begin();it!=this->student_list.end();it++){
            Student p=*it;
            if(p.id==id){
                cout<<"Enter the new name of the user\n";
                string name;
                getline(cin,name);
                it->Name=name;
                cout<<"Enter the new password of the user\n";
                string password;
                getline(cin,password);
                it->Password=password;
                break;
            }
        }
        if(it==this->student_list.end()){
            cout<<"Sorry but the user is not available\n";
        }
        else{
            cout<<"The user has been updated successfully\n";
        }
    }
    void update_professor(){                        //update professor details
        cout<<"Enter the id of the user you want to update\n";
        string id;
        getline(cin,id);
        auto it=this->professor_list.begin();
        for(it=this->professor_list.begin();it!=this->professor_list.end();it++){
            Professor p=*it;
            if(p.id==id){
                cout<<"Enter the new name of the user\n";
                string name;
                getline(cin,name);
                it->Name=name;
                cout<<"Enter the new password of the user\n";
                string password;
                getline(cin,password);
                it->Password=password;
                break;
            }
        }
        if(it==this->professor_list.end()){
            cout<<"Sorry but the user is not available\n";
        }
        else{
            cout<<"The user has been updated successfully\n";
        }
    }
    void update_librarian(){                        //update librarian details
        cout<<"Enter the id of the user you want to update\n";
        string id;
        getline(cin,id);

        auto it=this->librarian_list.begin();
        for(it=this->librarian_list.begin();it!=this->librarian_list.end();it++){
            Librarian p=*it;
            if(p.id==id){
                cout<<"Enter the new name of the user\n";
                string name;
                getline(cin,name);
                it->Name=name;
                cout<<"Enter the new password of the user\n";
                string password;
                getline(cin,password);
                it->Password=password;
                break;
            }
        }
        if(it==this->librarian_list.end()){
            cout<<"Sorry but the user is not available\n";
        }
        else{
            cout<<"The user has been updated successfully\n";
        }
    }
    void remove_student(){                          //remove student from the database
        cout<<"Enter the id of the user you want to remove\n";
        string id;
        getline(cin,id);
        auto it=this->student_list.begin();
        int f=0;
        for(it=this->student_list.begin();it!=this->student_list.end();it++){
            Student p=*it;
            if(p.id==id){
                f=1;
                this->student_list.erase(it);
                break;
            }
        }
        if(f==0){
            cout<<"Sorry but the user is not available\n";
        }
        else{
            cout<<"The user has been removed successfully\n";
        }
    }
    void remove_professor(){                        //remove professor from the database
        cout<<"Enter the id of the user you want to remove\n";
        string id;
        getline(cin,id);
        auto it=this->professor_list.begin();
        int f=0;
        for(it=this->professor_list.begin();it!=this->professor_list.end();it++){
            Professor p=*it;
            if(p.id==id){
                f=1;
                this->professor_list.erase(it);
                break;
            }
        }
        if(f==0){
            cout<<"Sorry but the user is not available\n";
        }
        else{
            cout<<"The user has been removed successfully\n";
        }
    }
    void remove_librarian(Librarian &librarian){    //remove librarian from the database
        cout<<"Enter the id of the user you want to remove\n";
        string id;
        getline(cin,id);
        if(librarian.id==id){
            cout<<"Sorry but you can't remove yourself\n";
            return;
        }
        auto it=this->librarian_list.begin();
        int f=0;
        for(it=this->librarian_list.begin();it!=this->librarian_list.end();it++){
            Librarian p=*it;
            if(p.id==id){
                f=1;
                this->librarian_list.erase(it);
                break;
            }
        }
        if(f==0){
            cout<<"Sorry but the user is not available\n";
        }
        else{
            cout<<"The user has been removed successfully\n";
        }
    }
    void list_all_users(){                          //list all users
        cout<<"This is list of all students: \n\n";
        for(auto it=this->student_list.begin();it!=this->student_list.end();it++){
            Student p=*it;
            cout<<"Name: "<<p.Name<<"\n";
            cout<<"ID: "<<p.id<<"\n";
            cout<<"\n";
        }
        cout<<"This is list of all professor: \n\n";
        for(auto it=this->professor_list.begin();it!=this->professor_list.end();it++){
            Professor p=*it;
            cout<<"Name: "<<p.Name<<"\n";
            cout<<"ID: "<<p.id<<"\n";
            cout<<"\n";
        }
        cout<<"This is list of all librarian: \n\n";
        for(auto it=this->librarian_list.begin();it!=this->librarian_list.end();it++){
            Librarian p=*it;
            cout<<"Name: "<<p.Name<<"\n";
            cout<<"ID: "<<p.id<<"\n";
            cout<<"\n";
        }
    }
};
void selected_option_student(User_db &user_db,Book_db &book_db,int pos_student,string option2){     //student selected option
    if(option2=="1"){
        book_db.list_all_books();
    }
    if(option2=="2"){
        user_db.list_all_books_of_user(user_db.student_list[pos_student].id);
    }
    if(option2=="3"){
        cout<<"Do you want to search by book title(1) or ISBN(2)\n";
        string option3;
        getline(cin,option3);
        if(option3=="1"){
            cout<<"Enter the book title\n";
            string title;
            getline(cin,title);
            book_db.search_book_by_Title(title);
        }
        if(option3=="2"){
            cout<<"Enter the book ISBN\n";
            string ISBN;
            getline(cin,ISBN);
            book_db.search_book_by_ISBN(ISBN);
        }
        if(option3!="1"&&option3!="2"){
            cout<<"Invalid option\n";
        }
    }
    if(option2=="4"){
         user_db.student_list[pos_student].issue_book(book_db);
    }
    if(option2=="5"){
         user_db.student_list[pos_student].submit_book(book_db);
    }
    if(option2=="6"){
         user_db.student_list[pos_student].Calculate_fine();
    }
    if(option2=="7"){
         user_db.student_list[pos_student].clear_fine();
    }
}
void selected_option_professor(User_db &user_db,Book_db &book_db,int pos_professor,string option2){    //professor selected option
    if(option2=="1"){
        book_db.list_all_books();
    }
    if(option2=="2"){
        user_db.list_all_books_of_user(user_db.professor_list[pos_professor].id);
    }
    if(option2=="3"){
        cout<<"Do you want to search by book title(1) or ISBN(2)\n";
        string option3;
        getline(cin,option3);
        if(option3=="1"){
            cout<<"Enter the book title\n";
            string title;
            getline(cin,title);
            book_db.search_book_by_Title(title);
        }
        if(option3=="2"){
            cout<<"Enter the book ISBN\n";
            string ISBN;
            getline(cin,ISBN);
            book_db.search_book_by_ISBN(ISBN);
        }
        if(option3!="1"&&option3!="2"){
            cout<<"Invalid option\n";
        }
    }
    if(option2=="4"){
        user_db.professor_list[pos_professor].issue_book(book_db);
    }
    if(option2=="5"){
        user_db.professor_list[pos_professor].submit_book(book_db);
    }
    if(option2=="6"){
        user_db.professor_list[pos_professor].Calculate_fine();
    }
    if(option2=="7"){
        user_db.professor_list[pos_professor].clear_fine();
    }
}
void selected_option_librarian(User_db &user_db,Book_db &book_db,int pos_librarian,string option2){   //librarian selected option
    if(option2=="1"){
        cout<<"Which type of user you want to add?\n";
        cout<<"1.Student\n";
        cout<<"2.Professor\n";
        cout<<"3.Librarian\n";
        string option4;
        getline(cin,option4);
        if(option4=="1"){
            user_db.add_student();
        }
        if(option4=="2"){
            user_db.add_professor();
        }
        if(option4=="3"){
            user_db.add_librarian();
        }
        if(option4!="1"&&option4!="2"&&option4!="3"){
            cout<<"Invalid option\n";
        }
    }
    if(option2=="2"){
        cout<<"Which type of user you want to remove?\n";
        cout<<"1.Student\n";   
        cout<<"2.Professor\n";
        cout<<"3.Librarian\n";
        string option4;    
        getline(cin,option4);
        if(option4=="1"){
            user_db.remove_student();
        }
        if(option4=="2"){
            user_db.remove_professor();
        }
        if(option4=="3"){
            user_db.remove_librarian(user_db.librarian_list[pos_librarian]);
        }
        if(option4!="1"&&option4!="2"&&option4!="3"){
            cout<<"Invalid option\n";
        }
    }
    if(option2=="3"){
        cout<<"Which type of user you want to update?\n";
        cout<<"1.Student\n";
        cout<<"2.Professor\n";
        cout<<"3.Librarian\n";
        string option4;
        getline(cin,option4);
        if(option4=="1"){
            user_db.update_student();
        }
        if(option4=="2"){
            user_db.update_professor();
        }
        if(option4=="3"){
            user_db.update_librarian();
        }
        if(option4!="1"&&option4!="2"&&option4!="3"){
            cout<<"Invalid option\n";
        }
    }
    if(option2=="4"){
        cout<<"Enter the book details\n";
        cout<<"Enter the book title\n";
        string title;
        getline(cin,title);
        cout<<"Enter the book author\n";
        string author;
        getline(cin,author);
        cout<<"Enter the book publisher\n";
        string publisher;
        getline(cin,publisher);
        string ISBN;
        cout<<"Enter the book ISBN\n";
        getline(cin,ISBN);
        book_db.add_book(Book(title,author,ISBN,publisher));
    }
    if(option2=="5"){
        cout<<"Enter the ISBN of the book you want to delete\n";
        string ISBN;
        getline(cin,ISBN);
        Book b=book_db.remove_book(ISBN);
        if(b.Title!=""){
            int f=0;
            auto it=user_db.student_list.begin();
            for(it=user_db.student_list.begin();it!=user_db.student_list.end();it++){
                  if(it->id==b.owner.second){
                     f=1;
                     auto id2=it->list_of_book.begin();
                     for(id2=it->list_of_book.begin();id2!=it->list_of_book.end();id2++){
                        if(id2->ISBN==b.ISBN){
                           it->list_of_book.erase(id2);
                           break;
                        }
                     }
                  }
            }
            if(f==0){
               auto it=user_db.professor_list.begin();
               for(it=user_db.professor_list.begin();it!=user_db.professor_list.end();it++){
                    if(it->id==b.owner.second){
                        f=1;
                        auto id2=it->list_of_book.begin();
                        for(id2=it->list_of_book.begin();id2!=it->list_of_book.end();id2++){
                            if(id2->ISBN==b.ISBN){
                                it->list_of_book.erase(id2);
                                break;
                            }
                        }
                    }
                }
            } 
        }
    }
    if(option2=="6"){
        cout<<"Enter the ISBN of the book you want to update\n";
        string ISBN;
        getline(cin,ISBN);
        Book b=book_db.update_book(ISBN);
        if(b.Title!="0"){
           int f=0;
           auto it=user_db.student_list.begin();
           for(it=user_db.student_list.begin();it!=user_db.student_list.end();it++){
               if(it->id==b.owner.second){
                  f=1;
                  auto id2=it->list_of_book.begin();
                  for(id2=it->list_of_book.begin();id2!=it->list_of_book.end();id2++){
                      if(id2->ISBN==b.ISBN){
                        id2->Author=b.Author;
                        id2->Publication=b.Publication;
                        id2->Title=b.Title;
                        id2->available=b.available;
                        id2->owner=b.owner;
                        id2->time_of_issue=b.time_of_issue;
                        break;
                      }
                  }
               }
           }
           if(f==0){
              auto it=user_db.professor_list.begin();
              for(it=user_db.professor_list.begin();it!=user_db.professor_list.end();it++){
                  if(it->id==b.owner.second){
                     f=1;
                     auto id2=it->list_of_book.begin();
                     for(id2=it->list_of_book.begin();id2!=it->list_of_book.end();id2++){
                        if(id2->ISBN==b.ISBN){
                           id2->Author=b.Author;
                           id2->Publication=b.Publication;
                           id2->Title=b.Title;
                           id2->available=b.available;
                           id2->owner=b.owner;
                           id2->time_of_issue=b.time_of_issue;
                           break;
                        }
                     }
                  }
               }
            }   
        }
    }
    if(option2=="7"){
        book_db.list_all_books();
    }
    if(option2=="8"){
        user_db.list_all_users();
    }
    if(option2=="9"){
        cout<<"Enter the user id\n";
        string id;
        getline(cin,id);
        user_db.list_all_books_of_user(id);
    }
    if(option2=="10"){
        cout<<"Enter the ISBN of the book whose owner you want\n";
        string ISBN;
        getline(cin,ISBN);
        auto it=book_db.list_of_books.begin();
        int f=0;
        for(it=book_db.list_of_books.begin();it!=book_db.list_of_books.end();it++){
            if(it->ISBN==ISBN){
                f=1;
                if(it->available==1){
                    cout<<"The book is in the library\n";
                }
                else{
                    cout<<"The owner of the book is : "<<"\n";
                    cout<<"Name: "<<it->owner.first<<"\n";
                    cout<<"ID: "<<it->owner.second<<"\n";
                }
                break;
            }
        }
        if(f==0){
            cout<<"No such book\n";
        }
    }
}
pair<int,int> login_as_student(User_db &user_db,Book_db &book_db){    // we take student credentials and then search in our db if found then we return student id
    string password,name;
    cout<<"Provide Name:";
    getline(cin,name);
    cout<<"Provide Password:";
    getline(cin,password);
    int y=0;
    for(auto it:user_db.student_list){          
        Student s=it;
        if(s.Name==name&&s.Password==password){
            cout<<"You have successfully logged in\n";
            return {1,y};
        }
        y++;
    }
    cout<<"Wrong username or password\n";
    return {0,-1};
}
pair<int,int> login_as_professor(User_db &user_db,Book_db &book_db){    // we take professor credentials and then search in our db if found then we return student id
    string password,name;
    cout<<"Provide Name:";
    getline(cin,name);
    cout<<"Provide Password:";
    getline(cin,password);
    int y=0;
    for(auto it:user_db.professor_list){
        Professor p=it;
        if(p.Name==name&&p.Password==password){
            cout<<"You have successfully logged in\n";
            return {2,y};
        }
        y++;
    }
    cout<<"Wrong username or password\n";
    return {0,-1};
}
pair<int,int> login_as_librarian(User_db &user_db,Book_db &book_db){    // we take librarian credentials and then search in our db if found then we return student id
    string password,name;
    cout<<"Provide Name:";
    getline(cin,name);
    cout<<"Provide Password:";
    getline(cin,password);
    int y=0;
    for(auto it:user_db.librarian_list){
        Librarian l=it;
        if(l.Name==name&&l.Password==password){
            cout<<"You have successfully logged in\n";
            return {3,y};
        }
        y++;
    }
    cout<<"Wrong username or password\n";
    return {0,-1};
}
int options_student(User_db &user_db,Book_db &book_db,int pos_student){ //to print the options available to student
    cout<<"1. List all books\n";
    cout<<"2. List books currently with me\n";
    cout<<"3. Check the avaibility of book\n";
    cout<<"4. Issue a book\n";
    cout<<"5. Submit a book\n";
    cout<<"6. Calculate fine\n";
    cout<<"7. Payfine\n";
    cout<<"8. Logout\n";
    string option2;
    getline(cin,option2);
    if(option2=="8"){
        return 0;
    }
    else{
        if(!(option2=="1"||option2=="2"||option2=="3"||option2=="4"||option2=="5"||option2=="6"||option2=="7"||option2=="8")){
            cout<<"Invalid option\n";
            return 1;
        }
        selected_option_student(user_db,book_db,pos_student,option2);
        return 1;
    }
}
int options_professor(User_db &user_db,Book_db &book_db,int pos_professor){ //to print the options available to professor
    cout<<"1. List all books\n";
    cout<<"2. List books currently with me\n";
    cout<<"3. Check the avaibility of book\n";
    cout<<"4. Issue a book\n";
    cout<<"5. Submit a book\n";
    cout<<"6. Calculate fine\n";
    cout<<"7. Payfine\n";
    cout<<"8. Logout\n";
    string option2;
    getline(cin,option2);
    if(option2=="8"){
        return 0;
    }
    else{
        if(!(option2=="1"||option2=="2"||option2=="3"||option2=="4"||option2=="5"||option2=="6"||option2=="7"||option2=="8")){
            cout<<"Invalid option\n";
            return 2;
        }
        selected_option_professor(user_db,book_db,pos_professor,option2);
        return 2;
    }
}
int options_librarian(User_db &user_db,Book_db &book_db,int pos_librarian){ //to print the options available to librarian
    cout<<"1. Add user\n";
    cout<<"2. Delete user\n";
    cout<<"3. Update user\n";
    cout<<"4. Add book\n";
    cout<<"5. Delete book\n";
    cout<<"6. Update book\n";
    cout<<"7. List all books\n";
    cout<<"8. List all users\n";
    cout<<"9. List the book issued to a user\n";
    cout<<"10. Check which user has a particular book\n";
    cout<<"11. Logout\n";
    string option2;
    getline(cin,option2);
    if(option2=="11"){
        return 0;
    }
    else{
        if(!(option2=="1"||option2=="2"||option2=="3"||option2=="4"||option2=="5"||option2=="6"||option2=="7"||option2=="8"||option2=="9"||option2=="10"||option2=="11")){
            cout<<"Invalid option\n";
            return 3;
        }
        selected_option_librarian(user_db,book_db,pos_librarian,option2);
        return 3;
    }
}
User_db user_db;
Book_db book_db;
int main(){
    int login=0;
    user_db.student_list.push_back(Student("harsh trivedi","-1","123"));      //dummy data
    user_db.librarian_list.push_back(Librarian("admin","-2","123")); //dummy data
    book_db.list_of_books.push_back(Book("new world1","madam curie","1","radio isotopie"));    //dummy data
    book_db.list_of_books.push_back(Book("Computer organisation","Halley paterson","2","pearson"));    //dummy data
    cout<<"Hii welcome to Library Management System\n";
    while(login==0){
        cout<<"Select one of the option below\n";
        cout<<"1. Login as Student\n";
        cout<<"2. Login as Professor\n";
        cout<<"3. Login as Librarian\n";
        string option;
        getline(cin,option);
        int pos_student;
        int pos_professor;
        int pos_librarian;
        if(option!="1"&&option!="2"&&option!="3"){
            cout<<"Please select a valid option\n";
        }
        if(option=="1"){
            auto temp=login_as_student(user_db,book_db);
            login=temp.first;               //here we set the value of login to 1 so that after each task instead of logging out we go back to option page fo student
            pos_student=temp.second;
        }
        if(option=="2"){
            auto temp=login_as_professor(user_db,book_db);
            login=temp.first;               //here we set the value of login to 2 so that after each task instead of logging out we go back to option page fo student
            pos_professor=temp.second;
        }
        if(option=="3"){
            auto temp=login_as_librarian(user_db,book_db);
            login=temp.first;               //here we set the value of login to 3 so that after each task instead of logging out we go back to option page fo student
            pos_librarian=temp.second;
        }
        if(login!=0){
            while(login!=0){                // for coming to opiton page until logout
                if(login==1){
                    login=options_student(user_db,book_db,pos_student);
                }
                if(login==2){
                    login=options_professor(user_db,book_db,pos_professor);
                }
                if(login==3){
                    login=options_librarian(user_db,book_db,pos_librarian);
                }
            }
        }
    }
}
