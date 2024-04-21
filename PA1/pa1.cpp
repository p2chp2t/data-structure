#include "utils.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/*
    [Task 1] Choose the TIGHT bound of the following arrayInsert function

    *arrayInsert*
        Input
        - int n: the length of the input arrays (n >=1)
        - int* A: an array storing n integers
        - int x: an element to insert
        - int pos : index position to insert element
        Output
        - int: The maximum product of elements from each A and B
        void arrayInsert(int n, int* A, int x, int pos) {
            n++;
            for (int i = n; i >= pos; i--)
                A[i] = A[i-1];
            A[pos – 1] = x;
            return;
        }

    Choices
        1: O( 1 )
        2: O( n )
        3: O( n log(n) )
        4: O( n^2 )
*/
void task_1(ofstream &fout) {
  int answer = 2; // TODO: Change to your answer

  fout << "[Task 1]" << endl;
  fout << answer << endl;

  return;
}

/*
    [Task 2] Choose the TIGHT bound of the following maxSubarraySum function

    *maxSubarraySum*
        Input
        - int n: the length of the input array (n >=1)
        - int* A: an array with n >=1 integers
        Output
        - int: maximum value of sum of subarray of A. Define subarray as { A[i],
   A[i+1], …, A[j] } for all integer i <= j < n. int maxSubarraySum(int n, int
   *A) { int max_sum = 0; for (int i = 0; i < n; i++) { for (int j = i; j < n;
   j++) { int cur_sum = 0; for (int k = i; k <= j; k++) { cur_sum += A[k];
                    }
                    if (cur_sum > max_sum){
                        max_sum = cur_sum;
                    }
                }
            }
            return max_sum;
        }

    Choices
        1: O( n log(n) )
        2: O( n )
        3: O( n^2 )
        4: O( n^3 )
*/
void task_2(ofstream &fout) {
  int answer = 4; // TODO: Change to your answer

  fout << "[Task 2]" << endl;
  fout << answer << endl;

  return;
}

/*
    [Task 3] List

    Description:
        Implement a function that can insert or replace an integer in the list.
        A user can insert or replace an element at the specific index.
        If the specified index is out of range of the given list, print “error”.

    Input:
        Sequence of commands, which is one of the following
        - (‘insert’,i): insert i into the i-th index in the list. i-th index
   indicates zero-based index.
        - (‘replace_at’,index): replace an element at the index to 0. index
   indicates zero-based index.

    Output:
        - An array after insertion/deletion in a string separated with the
   spacebar
        - “error” if the index is out of range
*/
void task_3(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  const int MAX_SIZE = 100000;
  int list[MAX_SIZE];
  int size = 0;

  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    if (command.compare("insert") == 0) {
      /* TODO: Implement */
      int index = instr_seq->instructions[i].value; //삽입할 원소
      if (size == 0) {                              //빈 배열인 경우
        if (index != 0) {
          size = -100;
          answer = "error";
          break;
        }
        list[size] = instr_seq->instructions[i].value;
        size++;
      } else {                           //배열이 비어 있지 않은 경우
        if (index < 0 || index > size) { // index is out of range
          size = -100;
          answer = "error";
          break;
        }
        //삽입 위치 오른쪽에 있는 원소들을 한칸씩 이동시키기
        for (int j = size - 1; j >= index; j--) {
          list[j + 1] = list[j];
        }
        list[index] = index; // insert
        size++;              //배열의 크기 업데이트
      }
    } else if (command.compare("replace_at") == 0) {
      /* TODO: Implement */
      if (instr_seq->instructions[i].value < 0 ||
          instr_seq->instructions[i].value >= size) {
        size = -100;
        answer = "error";
        break;
      }
      list[instr_seq->instructions[i].value] = 0; // 0으로 값 채우기
    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }
  }
  if (size >= 0) { //에러가 나지 않고 정상적으로 실행된 경우
    for (int i = 0; i < size; i++) { // answer에 list의 값들 저장
      answer += to_string(list[i]);
      answer += " ";
    }
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 3]" << endl;
  fout << answer << endl;
}

/*
    [Task 4] Stack

    Description:
        Implement a function that prints the top values of the stack when “top”
   operation is called after the sequence of “push” or “pop” operations. If the
   “top” operation is called for an empty stack, print “-1”, If “pop” operation
   is called for an empty stack, print “error” and the program terminates. The
   stack can contain positive integers.

    Input:
        Sequence of commands, which is one of the following,
        - (‘push’,integer): push integer into the current stack, if integer is
   negative, skip the push step
        - (‘pop’,NULL): pop the top value of the current stack (this operation
   will print nothing)
        - (‘top’,NULL): print the top value of the current stack (print ‘-1’ if
   the current stack is empty)

    Output:
        - Expected printed values after processing the whole sequence, in a
   string separated with the spacebar
        - “error” if the pop operation is executed on an empty stack, and then
   the program terminates.

*/
void task_4(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  const int MAX_SIZE = 100000;
  int list[MAX_SIZE];
  int size = 0;

  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    if (command.compare("push") == 0) {
      /* TODO: Implement */
      if (instr_seq->instructions[i].value < 0)
        continue;
      list[size] = instr_seq->instructions[i].value;
      size++;
    } else if (command.compare("pop") == 0) {
      /* TODO: Implement */
      if (size == 0) {
        answer = "error";
        break;
      } else
        size--;
    } else if (command.compare("top") == 0) {
      /* TODO: Implement */
      if (size == 0) {
        int ans = -1;
        answer = to_string(ans);
        break;
      } else {
        answer += to_string(list[size - 1]);
        answer += " ";
      }
    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 4]" << endl;
  fout << answer << endl;
}

/*
    [Task 5] Circular Queue

    Desctiption:
        Implement a function that shows the values in a circular queue with a
   Boolean indicator. If the queue after the operations is empty, print “empty”.
        If “enqueue” operates on a full queue or if “dequeue” operates on an
   empty queue, print “error”. The maximum number of elements (n) in the queue
   is four.

    Input:
        Sequence of commands, which is one of the following,
        - (‘enqueue’,integer): enqueue integer into the current queue
        - (‘dequeue’,NULL): dequeue from the current queue

    Output
        - Values in the circular queue (mod size n = 4), from the front to the
   rear. String separated with the spacebar, empty memory shows NULL
        - “empty” if the queue is empty when the operations are terminated
   normally
        - “error” if the “dequeue” operation is executed on an empty queue or if
   the “enqueue” operation is executed on a full queue
*/
void task_5(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;
  int queue_size = 4;
  int queue[4] = {};
  bool is_empty = true;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int front = 0;
  int rear = 0;
  int size = 0;

  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    if (command.compare("enqueue") == 0) {
      /* TODO: Implement */
      int value = instr_seq->instructions[i].value;
      if (size == queue_size) { // full queue
        answer = "error";
        break;
      } else {
        queue[rear] = value;
        rear = (rear + 1) % queue_size;
        size++;
        is_empty = false;
      }
    } else if (command.compare("dequeue") == 0) {
      /* TODO: Implement */
      if (size == 0) { // empty queue
        answer = "error";
        break;
      } else {
        front = (front + 1) % queue_size;
        size--;
        if (front == rear)
          is_empty = true;
      }
    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }
  }
  if (answer == "error")
    ;
  else if (is_empty) {
    answer = "empty";
  } else {
    for (int i = 0; i < size; i++) {
      answer += to_string(queue[front]);
      answer += " ";
      front = (front + 1) % queue_size;
    }
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 5]" << endl;
  fout << answer << endl;
}

/*
    [Task 6] Double-Ended Queue

    Description:
        Implement a function that shows the values in a double-ended queue
   (deque) whose maximum number of elements is four. If “insert” is called for
   an already full deque or the “erase” operation is called for an empty deque,
   there should be no changes to the queue.

    Input:
        Sequence of commands, which is one of the following,
        - (‘insert_front’,integer): insert integer at the beginning of the
   deque.
        - (‘insert_back’,integer): insert integer at the end of the deque.
        - (‘erase_front’,NULL): erase the first element the queue.
        - (‘erase_back’,NULL): erase the last element the queue.

    Output
        - Values in the queue from the beggining to the end, in a string
   separated with spacebar
        - “empty” if the queue is empty
*/
void task_6(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int deque[4];
  int front = 0;
  int rear = 3;
  int size = 0;

  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    if (command.compare("insert_front") == 0) {
      /* TODO: Implement */
      int value = instr_seq->instructions[i].value;

      front = (front + 3) % 4;
      if (size == 4) {
        continue;
      }
      deque[front] = value;
      size++;
    } else if (command.compare("insert_back") == 0) {
      /* TODO: Implement */
      int value = instr_seq->instructions[i].value;
      rear = (rear + 1) % 4;
      if (size == 4) {
        continue;
      }
      deque[rear] = value;
      size++;
    } else if (command.compare("erase_front") == 0) {
      /* TODO: Implement */
      if (size == 0)
        continue;
      front = (front + 1) % 4;
      size--;
    } else if (command.compare("erase_back") == 0) {
      /* TODO: Implement */
      if (size == 0)
        continue;
      rear = (rear + 3) % 4;
      size--;
    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }
  }
  if (size == 0) {
    answer = "empty";
  } else {
    for (int i = 0; i < size; i++) {
      int index = (front + i) % 4;
      answer += to_string(deque[index]);
      answer += " ";
    }
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 6]" << endl;
  fout << answer << endl;
}

int main(int argc, char **argv) {
  string filename = "submit.txt";
  int task_num = 0;
  InstructionSequence *instr_seq;

  // Open file
  ofstream fout;
  fout.open(filename, fstream::app);
  if (!fout.is_open()) {
    cerr << "Unable to open file: " << filename << endl;
    return -1;
  }

  // Choosing task number. Default is running ALL tasks (0)
  if (argc >= 2)
    task_num = atoi(argv[1]);
  if (argc >= 3) {
    try {
      instr_seq = ParseInstructions(argv[2]);
    } catch (const char *e) {
      cerr << e << endl;
      return -1;
    }
  }

  // Running the task(s)
  switch (task_num) {
  case 1:
    task_1(fout);
    break;
  case 2:
    task_2(fout);
    break;
  case 3:
    task_3(fout, instr_seq);
    break;
  case 4:
    task_4(fout, instr_seq);
    break;
  case 5:
    task_5(fout, instr_seq);
    break;
  case 6:
    task_6(fout, instr_seq);
    break;
  case 0:
    task_1(fout);
    task_2(fout);

    InstructionSequence *instr_seq_3;
    instr_seq_3 = ParseInstructions(TASK_3_DEFAULT_ARGUMENT);
    task_3(fout, instr_seq_3);

    InstructionSequence *instr_seq_4;
    instr_seq_4 = ParseInstructions(TASK_4_DEFAULT_ARGUMENT);
    task_4(fout, instr_seq_4);

    InstructionSequence *instr_seq_5;
    instr_seq_5 = ParseInstructions(TASK_5_DEFAULT_ARGUMENT);
    task_5(fout, instr_seq_5);

    InstructionSequence *instr_seq_6;
    instr_seq_6 = ParseInstructions(TASK_6_DEFAULT_ARGUMENT);
    task_6(fout, instr_seq_6);
    break;
  default:
    cout << "Wrong task number" << endl;
  }

  fout.close();
  return 0;
}
