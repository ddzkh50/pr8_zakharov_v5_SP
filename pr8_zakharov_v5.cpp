#include <exception>
#include <iostream>
#include <string>
using namespace std;

struct Task {
  char title[60];
  int priority;
  bool completed;

  Task* next;
  Task* prev;

  Task(string t, int p, bool c){
      int i = 0;
      for (;i < t.length() && i < 59; i++){
          title[i] = t[i];
      }
      title[i] = '\0';

      priority = p;
      completed = c;
      next = nullptr;
      prev = nullptr;
  }
};

class DoubleList{
    private:
        Task* head = nullptr;
        Task* tail = nullptr;
        Task* selectedTask = nullptr;

        void initialize_list(){
            selectedTask = head;
        }

        static string getStringFromTitle(Task* task){
            return string(task->title);
        }

    public:
        DoubleList(){}

        void delete_list(){
            Task* current = head;
            while (current != nullptr){
                Task* next = current->next;
                delete current;
                current = next;
            }

            head = nullptr;
            tail = nullptr;
            selectedTask = nullptr;
        }

        string getTask(Task* task){
            return "\nTitle: " + getStringFromTitle(task) + "\nPriority: " + to_string(task->priority)
            + "\nComplete: " + to_string(task->completed) + "\n";
        }

        Task* getSelectedTask(){
            if (selectedTask != nullptr) {
                return  selectedTask;
            }
            return nullptr;
        }

        void push_front(string title, int priority, bool completed){
            Task* task = new Task(title, priority, completed);

            if (head == nullptr){
                head = task;
                tail = task;
            }
            else {
                task->next = head;
                head->prev = task;
                head = task;
            }

            initialize_list();
        }
        void push_back(string title, int priority, bool completed){
            Task* task = new Task(title, priority, completed);

            if (tail == nullptr){
                head = task;
                tail = task;
            }
            else{
                task->prev = tail;
                tail->next = task;
                tail = task;
            }
            initialize_list();
        }
        void pop_front(){
            if (head == nullptr){
                cout << "\nNothing to delete" << "\n";
                return;
            }

            Task* temp = head;
            if (head == tail){
                head = nullptr;
                tail = nullptr;
                selectedTask = nullptr;
            }
            else{
                head = head->next;
                head->prev = nullptr;
                if (selectedTask == temp){
                    selectedTask = head;
                }
            }
            delete temp;
        }
        void pop_back(){
            if (tail == nullptr){
                cout << "\nNothing to delete" << "\n";
                return;
            }

            Task* temp = tail;
            if (head == tail){
                head = nullptr;
                tail = nullptr;
                selectedTask = nullptr;
            }
            else{
                tail = tail->prev;
                tail->next = nullptr;
                if (selectedTask == temp){
                    selectedTask = tail;
                }
            }
            delete temp;
        }
        void display_forward(){
            Task* current = head;

            while(current != nullptr){
                cout << getTask(current);
                current = current->next;
            }
        }
        void display_backward(){
            Task* current = tail;

            cout << "\nAll list\n";
            while (current != nullptr){
                cout << getTask(current);
                current = current->prev;
            }
        }
        void search(){
            int maxPriority = -999;
            Task* current = head;
            bool isFounded = false;

            while (current != nullptr){
                if (current->priority > maxPriority && current->completed == false) maxPriority = current->priority;
                current = current->next;
            }
            current = head;
            while (current != nullptr){
                if (current->priority == maxPriority &&
                    current->completed == false){
                        cout << getTask(current);
                        isFounded = true;
                    }
                current = current->next;
            }

            if (isFounded == false) cout << "\nElement is not found\n";
        }
        void deleteNotCompleted(){
            Task* current = head;

            while (current != nullptr){
                if (!current->completed){
                    if (current->prev != nullptr){
                        current->prev->next = current->next;
                    }
                    else {
                        head = current->next;
                    }
                    if (current->next != nullptr){
                        current->next->prev = current->prev;
                    }
                    else {
                        tail = current->prev;
                    }
                    if (selectedTask == current){
                        selectedTask = current->next;
                    }
                }
                current = current->next;
                delete current;
            }
            if (head == nullptr){
                selectedTask = nullptr;
            }
        }
        void next(){
            if (selectedTask != nullptr && selectedTask->next != nullptr)
                selectedTask = selectedTask->next;
        }
        void prev(){
            if (selectedTask != nullptr && selectedTask->prev != nullptr)
                selectedTask = selectedTask->prev;
        }
        void SelectedtaskToEnd(){
            if (selectedTask == nullptr || selectedTask == tail){
                return;
            }

            if (selectedTask->prev != nullptr){
                selectedTask->prev->next = selectedTask->next;
            }
            else{
                head = selectedTask->next;
            }

            if (selectedTask->next != nullptr){
                selectedTask->next->prev = selectedTask->prev;
            }

            selectedTask->prev = tail;
            selectedTask->next = nullptr;

            tail->next = selectedTask;
            tail = selectedTask;
        }
        void SelectedTask(){
            if (selectedTask == nullptr){
                cout << "\nNothing selected\n";
                return;
            }

            Task* temp = selectedTask;
            if (selectedTask->next != nullptr){
                selectedTask = selectedTask->next;
            }
            else if (selectedTask->prev != nullptr) {
                selectedTask = selectedTask->prev;
            }
            else {
                selectedTask = nullptr;
                return;
            }

            if (temp->prev != nullptr){
                temp->prev->next = temp->next;
            }
            else{
                head = temp->next;
            }

            if (temp->next != nullptr){
                temp->next->prev = temp->prev;
            }
            else{
                tail = temp->prev;
            }
            delete temp;
        }
};

int main(){
    int input = -1;
    int temp;
    DoubleList list = DoubleList();

    string title;
    int priority;
    bool isCompleted;
    try {
        while(input != 0) {
            cout << "\n\n1. Add task to start"
                << "\n2. Add task to end"
                << "\n3. Delete first task"
                << "\n4. Delete last task"
                << "\n5. Show all task list"
                << "\n6. Show all task list from end"
                << "\n7. Find task with max priority"
                << "\n8. Delete all not completed tasks"
                << "\n9. Put selected task to end"
                << "\n10. Select next task"
                << "\n11. Select previous task"
                << "\n12. Delete task list"
                << "\n0. Exit\n\n";

            if (list.getSelectedTask() != nullptr){
                cout << "\nSelected task now is:" << list.getTask(list.getSelectedTask()) << "\n";
            }
            cin >> input;

            switch (input) {
                case 1:{
                    cout << "\nEnter task title" << "\n"; cin >> title;
                    cout << "\nEnter task priority" << "\n"; cin >> priority;
                    cout << "\nEnter is task complete (0:1)"; cin >> temp;
                    if (temp == 0) isCompleted = false;
                    else isCompleted = true;

                    list.push_front(title, priority, isCompleted);
                    cout << "\nTask added\n";
                    break;
                    }
                case 2:{
                    cout << "\nEnter task title" << "\n"; cin >> title;
                    cout << "\nEnter task priority" << "\n"; cin >> priority;
                    cout << "\nEnter is task complete (0:1)"; cin >> temp;
                    if (temp == 0) isCompleted = false;
                    else isCompleted = true;

                    list.push_back(title, priority, isCompleted);
                    cout << "\nTask added\n";
                    break;
                    }
                case 3:{
                    list.pop_front();
                    break;
                    }
                case 4:{
                    list.pop_back();
                    break;
                    }
                case 5:{
                    list.display_forward();
                    break;
                    }
                case 6:{
                    list.display_backward();
                    break;
                    }
                case 7:{
                    list.search();
                    break;
                    }
                case 8:{
                    list.deleteNotCompleted();
                    break;
                    }
                case 9:{
                    list.SelectedtaskToEnd();
                    break;
                    }
                case 10:{
                    list.next();
                    break;
                    }
                case 11:{
                    list.prev();
                    break;
                    }
                case 12:{
                    list.delete_list();
                    break;
                    }
            }

        }
    } catch (exception) {
        cout << "\nError\n";
    }
}
