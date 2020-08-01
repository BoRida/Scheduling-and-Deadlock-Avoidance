//Boris Huang

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>

//note this program assumes that each line in the input follows the same parameter order every time

class OS { //has the submit queue, holding queues, ready queue, wait queue, and complete queue
  private:

  public:
    int time = 0; //this is the ultimate counter for the time
    int main_memory;
    int num_serial_devices;
    int time_quantum = 1;
    int max_main_memory; //never changed.
    int max_num_serial_devices; //maybe should use const or final or whatever
    OS() { //Constructor

    }
    OS(int mm, int nsd, int tq) { //probably never going to be used
      main_memory = mm;
      num_serial_devices = nsd;
      time_quantum = tq;
    }

    //methods and queues
    std::queue<std::vector<int>> submit_queue; // job_number,required_main_memory,max_devices,run_time,priority
    std::queue<std::vector<int>> hold_queue_1; //job_number, required_main_memory,max_devices,run_time,priority(which determines which hq)
    std::queue<std::vector<int>> hold_queue_2; //job_number, required_main_memory,max_devices,run_time,priority(which determines which hq)
    std::queue<std::vector<int>> ready_queue; //job_number, required_main_memory,num_devices,run_time,priority
    std::queue<std::vector<int>> wait_queue; //job_number, required_main_memory,num_devices,run_time,priority
    std::queue<std::vector<int>> complete_queue; //job_number, required_main_memory,num_devices,run_time,priority, time_finished
    std::vector<std::vector<int>> jobs; //job_number, required_main_memory,num_devices,run_time,priority,submission_time


    std::vector<std::vector<int>> requests; //replaces methods


    void display() {

      std::cout << "DISPLAY" << std::endl;
      std::cout << "**************************" << std::endl << std::endl;

      std::cout << "System currently using " << this->max_main_memory - this->main_memory << " of " << this->max_main_memory << " units of memory" << std::endl;
      std::cout << "System currently using " << this->max_num_serial_devices - this->num_serial_devices << " of " << this->max_num_serial_devices << " serial devices" << std::endl;
      std::cout << "Jobs: " << std::endl << std::endl;
      for (int i =0; i<this->jobs.size(); i++) {
        std::cout << "Job Number " << jobs[i][0] << " has " << this->jobs[i][3] << " more units of time" << std::endl;

      }
      std::cout << std::endl;

      //print contents of each queue
      std::cout << "Contents of Submit Queue: " << std::endl;
      std::vector<int> temp_vector_s; //vector to help iterate
      int original_submit_size;
      original_submit_size = this->submit_queue.size(); //need this to help put items back in queue
      for (int i = 0; i<original_submit_size; i++) {
        temp_vector_s = this->submit_queue.front();
        this->submit_queue.pop();
        std::cout << "Job Number " << temp_vector_s[0] << ": requires " << temp_vector_s[1] << " units of main memory, holds " <<
        temp_vector_s[2] << " devices, runs for " << temp_vector_s[3] << " units of time, and has a priority of " <<
        temp_vector_s[4] << std::endl;
        this->submit_queue.push(temp_vector_s);
      }
      if (this->submit_queue.empty()) {
        std::cout << "EMPTY" << std::endl;
      }
      std::cout << std::endl;

      std::cout << "Contents of Holding Queue 1: " << std::endl;
      std::vector<int> temp_vector_h1; //vector to help iterate
      int original_h1_size;
      original_h1_size = this->hold_queue_1.size(); //need this to help put items back in queue
      for (int i = 0; i<original_h1_size; i++) {
        temp_vector_h1 = this->hold_queue_1.front();
        this->hold_queue_1.pop();
        std::cout << "Job Number " << temp_vector_h1[0] << ": requires " << temp_vector_h1[1] << " units of main memory, holds " <<
        temp_vector_h1[2] << " devices, runs for " << temp_vector_h1[3] << " units of time, and has a priority of " <<
        temp_vector_h1[4] << std::endl;
        this->hold_queue_1.push(temp_vector_h1);
      }
      if (this->hold_queue_1.empty()) {
        std::cout << "EMPTY" << std::endl;
      }
      std::cout << std::endl;

      std::cout << "Contents of Holding Queue 2: " << std::endl;
      std::vector<int> temp_vector_h2; //vector to help iterate
      int original_h2_size;
      original_h2_size = this->hold_queue_2.size(); //need this to help put items back in queue
      for (int i = 0; i<original_h2_size; i++) {
        temp_vector_h2 = this->hold_queue_2.front();
        this->hold_queue_2.pop();
        std::cout << "Job Number " << temp_vector_h2[0] << ": requires " << temp_vector_h2[1] << " units of main memory, holds " <<
        temp_vector_h2[2] << " devices, runs for " << temp_vector_h2[3] << " units of time, and has a priority of " <<
        temp_vector_h2[4] << std::endl;
        this->hold_queue_2.push(temp_vector_h2);
      }
      if (this->hold_queue_2.empty()) {
        std::cout << "EMPTY" << std::endl;
      }
      std::cout << std::endl;

      //print contents of each queue
      std::cout << "Contents of Ready Queue: " << std::endl;
      std::vector<int> temp_vector_r; //vector to help iterate
      int original_ready_size;
      original_ready_size = this->ready_queue.size(); //need this to help put items back in queue
      for (int i = 0; i<original_ready_size; i++) {
        temp_vector_r = this->ready_queue.front();
        this->ready_queue.pop();
        std::cout << "Job Number " << temp_vector_r[0] << ": requires " << temp_vector_r[1] << " units of main memory, holds " <<
        temp_vector_r[2] << " devices, runs for " << temp_vector_r[3] << " units of time, and has a priority of " <<
        temp_vector_r[4] << std::endl;
        this->ready_queue.push(temp_vector_r);
      }
      if (this->ready_queue.empty()) {
        std::cout << "EMPTY" << std::endl;
      }
      std::cout << std::endl;

      //print contents of each queue
      std::cout << "Contents of Wait Queue: " << std::endl;
      std::vector<int> temp_vector_w; //vector to help iterate
      int original_wait_size;
      original_wait_size = this->wait_queue.size(); //need this to help put items back in queue
      for (int i = 0; i<original_wait_size; i++) {
        temp_vector_w = this->wait_queue.front();
        this->wait_queue.pop();
        std::cout << "Job Number " << temp_vector_w[0] << ": requires " << temp_vector_w[1] << " units of main memory, holds " <<
        temp_vector_w[2] << " devices, runs for " << temp_vector_w[3] << " units of time, and has a priority of " <<
        temp_vector_w[4] << std::endl;
        this->wait_queue.push(temp_vector_w);
      }
      if (this->wait_queue.empty()) {
        std::cout << "EMPTY" << std::endl;
      }
      std::cout << std::endl;

      //print contents of each queue
      std::cout << "Contents of Complete Queue: " << std::endl;
      std::vector<int> temp_vector_c; //vector to help iterate
      int original_complete_size;
      original_complete_size = this->complete_queue.size(); //need this to help put items back in queue
      for (int i = 0; i<original_complete_size; i++) {
        temp_vector_c = this->complete_queue.front();
        this->complete_queue.pop();
        std::cout << "Job Number " << temp_vector_c[0] << ": requires " << temp_vector_c[1] << " units of main memory, holds " <<
        temp_vector_c[2] << " devices, finished after " << temp_vector_c[3] << " units of time, and has a priority of " <<
        temp_vector_c[4] << std::endl;
        std::cout << "Turnaround Time: " << temp_vector_c[3]-temp_vector_c[5] << ", Weighted Turnaround Time: " << (temp_vector_c[3]-temp_vector_c[5])/this->time_quantum << std::endl;
        std::cout << std::endl;
        this->complete_queue.push(temp_vector_c);
      }
      if (this->complete_queue.empty()) {
        std::cout << "EMPTY" << std::endl;
      }
      std::cout << std::endl;







      std::cout << std::endl << "**************************" << std::endl;
    }

    void run() {

      //submit queue -> hold queues
      if (submit_queue.empty() != true) {


        std::vector<int> temp_vector;
        //temp_vector.swap(this->submit_queue.front());
        temp_vector = this->submit_queue.front();

        //0 -> job number
        //1 -> main main_memory
        //2 -> num_serial_devices
        //3 -> run_time
        //4 -> priority

        if (temp_vector[4] == 1 && temp_vector[1] <= this->max_main_memory && temp_vector[2] <= this->max_num_serial_devices) { //put in hq1
          this->hold_queue_1.push(temp_vector);
        }
        else if (temp_vector[4] == 2 && temp_vector[1] <= this->max_main_memory && temp_vector[2] <= this->max_num_serial_devices) { //put in hq2
          this->hold_queue_2.push(temp_vector);
        }
        this->submit_queue.pop();
      }



      //holding queues -> ready_queue
      if (this->hold_queue_1.empty() != true) { //SJF
        //finds shortest job and puts it in the front

        int shortest_job;
        int shortest_job_size = 1000000; //arbitrarily long int
        int original_h1_size = this->hold_queue_1.size();
        int num_iterations;


        for (int i = 0; i<original_h1_size; i++) { //iterate through once first to find shortest job
          std::vector<int> temp_vector; //new temp_vector in the hold_queue_1
          temp_vector = this->hold_queue_1.front();
          if (temp_vector[3] < shortest_job) {
            shortest_job_size = temp_vector[3];
            shortest_job = temp_vector[0];
            num_iterations = i;
          }
          this->hold_queue_1.pop();
          this->hold_queue_1.push(temp_vector);
        }

        for (int i = 0; i<num_iterations; i++) {
          std::vector<int> temp_vector;
          temp_vector = this->hold_queue_1.front();
          this->hold_queue_1.pop();
          this->hold_queue_1.push(temp_vector);
        }


        std::vector<int> temp_vector;
        temp_vector = this->hold_queue_1.front(); //this should now be the shortest job

        if (this->main_memory >= temp_vector[1] && this->num_serial_devices >= temp_vector[2]) {
          this->main_memory -= temp_vector[1]; //can only be gotten back when a request for release is made or job is done
          this->num_serial_devices -= temp_vector[2];
          this->hold_queue_1.pop();
          this->ready_queue.push(temp_vector);
        }
      }
      else if (this->hold_queue_1.empty() == true && this->hold_queue_2.empty() != true) { //H2 instead
        std::vector<int> temp_vector; //new temp_vector in the hold_queue_2
        temp_vector = this->hold_queue_2.front();
        if (this->main_memory >= temp_vector[1] && this->num_serial_devices >= temp_vector[2]) {
          this->main_memory -= temp_vector[1]; //can only be gotten back when a request for release is made or job is done
          this->num_serial_devices -= temp_vector[2];
          this->hold_queue_2.pop();
          this->ready_queue.push(temp_vector);
        }
      }


      //requests here
      int r;
      for (r = 0; r<requests.size(); r++) {
        if (this->time > requests[r][0] && requests[r][0] != 0) { //0 means request is done
          int original_ready_size = this->ready_queue.size();
          if (this->ready_queue.empty() != true) {
            for (int j = 0; j<original_ready_size; j++) { //search through ready
              std::vector<int> temp_vector;
              temp_vector = this->ready_queue.front();
              if (requests[r][1] == temp_vector[0]) { //if same job found (meaning no errors)
                if (this->num_serial_devices >= (requests[r][2]*(-1))) {
                  temp_vector[2] -= requests[r][2];
                  this->num_serial_devices += requests[r][2];
                  requests[r][0] = 0; //request is now done
                }
                else { //put job in wait_queue
                  //this->wait_queue.push(temp_vector);
                  //this->ready_queue.pop();
                }
              }
              this->ready_queue.pop();
              this->ready_queue.push(temp_vector);
            }

          }
          int original_wait_size = this->wait_queue.size();
          if (this->wait_queue.empty() != true) {
            for (int k = 0; k<original_wait_size; k++) {
              std::vector<int> temp_vector;
              temp_vector = this->wait_queue.front();
              if (requests[r][1] == temp_vector[0]) { //if same job found (meaning no errors)
                if (this->num_serial_devices >= (requests[r][2]*(-1))) {
                  temp_vector[2] -= requests[r][2];
                  this->num_serial_devices += requests[r][2];
                  requests[r][0] = 0; //request is now done
                }

              }
              this->wait_queue.pop();
              this->wait_queue.push(temp_vector);
            }
          }
        }
      }


      //ready_queue -> wait_queue
      if (!this->ready_queue.empty()) {
        int original_ready_size = this->ready_queue.size();
        for (int i = 0; i<original_ready_size; i++) {
          std::vector<int> temp_vector;
          temp_vector = this->ready_queue.front();
          this->ready_queue.pop();
          if (temp_vector[2] > this->num_serial_devices) {
            this->wait_queue.push(temp_vector);
          }
          else {
            this->ready_queue.push(temp_vector);
          }
        }
      }

      //wait_queue -> ready_queue
      if (!this->wait_queue.empty()) {
        int original_wait_size = this->wait_queue.size();
        for (int i = 0; i<original_wait_size; i++) {
          std::vector<int> temp_vector;
          temp_vector = this->wait_queue.front();
          this->wait_queue.pop();
          if (this->num_serial_devices>=0) {
            this->ready_queue.push(temp_vector);
          }
          else {
            this->wait_queue.push(temp_vector);
          }
        }
      }


      //run
      //run -> ready_queue
      //run -> complete_queue
      if (this->ready_queue.empty() != true) { //changed from while to if
        std::vector<int> temp_vector;
        temp_vector = this->ready_queue.front();

        for (int i = 0; i<this->jobs.size(); i++) { //updates time for each job in the job vector
          if (temp_vector[0] == this->jobs[i][0]) {
            jobs[i][3] -= this->time_quantum;
            if (this->jobs[i][3] < 0) {
              this->jobs[i][3] = 0;
            }
          }
        }
        temp_vector[3] -= this->time_quantum;



        if (temp_vector[3] <= 0) { //if time_running is done, goes to complete, [3] becomes time completed
          temp_vector[3] = this->time;
          this->main_memory += temp_vector[1];
          this->num_serial_devices += temp_vector[2];
          temp_vector[2] = 0;
          this->complete_queue.push(temp_vector);

        }

        else if (temp_vector[3] > 0) { //goes back to ready_queue, unless request_devices came in
          this->ready_queue.push(temp_vector);
        }
        this->ready_queue.pop();
      }











      this->time += this->time_quantum;
    }


};



int main() {

  OS testOS;

  std::string line;
  std::ifstream myfile("input.txt");
  if (myfile.is_open()) {
    while (getline (myfile,line)) {
      if (line[0] == 'C') { //uses the System Configuration line to basically instantiate the "new" OS class
      //M = main_memory, S = num_serial_devices, Q = time_quantum

        //std::string test = "C 1 M=200 S=12 Q=4";
        std::string::size_type first_space = line.find(' ',0);
        std::string::size_type second_space = line.find(' ', first_space+1);
        std::string::size_type third_space = line.find(' ', second_space+1);
        std::string::size_type fourth_space = line.find(' ', third_space+1);

        testOS.time = std::stoi(line.substr(first_space+1,second_space-first_space));
        testOS.main_memory = std::stoi(line.substr(second_space+3,third_space-second_space));
        testOS.num_serial_devices = std::stoi(line.substr(third_space+3,fourth_space-third_space));
        testOS.max_main_memory = testOS.main_memory;
        testOS.max_num_serial_devices = testOS.num_serial_devices;
        testOS.time_quantum = std::stoi(line.substr(fourth_space+3,line.length()-fourth_space));

      }
      else if (line[0] == 'A') { //job arrival, J = job number, M = units of main_memory required, S = num devices held at a time
        //R = amount of units of time is run, P = Priority, 1 or 2
        std::string::size_type first_space = line.find(' ',0);
        std::string::size_type second_space = line.find(' ', first_space+1);
        std::string::size_type third_space = line.find(' ', second_space+1);
        std::string::size_type fourth_space = line.find(' ', third_space+1);
        std::string::size_type fifth_space = line.find(' ', fourth_space+1);
        std::string::size_type sixth_space = line.find(' ', fifth_space+1);

        int time = std::stoi(line.substr(first_space+1,second_space-first_space));
        int job_number = std::stoi(line.substr(second_space+3,third_space-second_space));
        int required_main_memory = std::stoi(line.substr(third_space+3,fourth_space-third_space));
        int max_devices = std::stoi(line.substr(fourth_space+3,fifth_space-fourth_space));
        int run_time = std::stoi(line.substr(fifth_space+3,sixth_space-fifth_space));
        int priority = std::stoi(line.substr(sixth_space+3,line.length()-sixth_space));


        while (testOS.time<time) {
          testOS.run();
        }
        std::vector<int> temp_vector;
        temp_vector.push_back(job_number);
        temp_vector.push_back(required_main_memory);
        temp_vector.push_back(0); //pushes 0 since all jobs presumably start using 0 devices, if I'm understanding this correctly
        temp_vector.push_back(run_time);
        temp_vector.push_back(priority);
        temp_vector.push_back(time);
        testOS.submit_queue.push(temp_vector);
        testOS.jobs.push_back(temp_vector);



      }
      else if (line[0] == 'Q') { //request for devices
      //J = job number, D = num_devices_requested
        std::string::size_type first_space = line.find(' ',0);
        std::string::size_type second_space = line.find(' ', first_space+1);
        std::string::size_type third_space = line.find(' ', second_space+1);

        int time = std::stoi(line.substr(first_space+1,second_space-first_space));
        int job_number = std::stoi(line.substr(second_space+3,third_space-second_space));
        int num_devices_requested = std::stoi(line.substr(third_space+3,line.length()-third_space));

        while (testOS.time<time) {
          testOS.run();
        }
        std::vector<int> temp_vector;
        temp_vector.push_back(time);
        temp_vector.push_back(job_number);
        num_devices_requested *= -1;
        temp_vector.push_back(num_devices_requested);
        testOS.requests.push_back(temp_vector);


      }
      else if (line[0] == 'L') { //release for devices
      //J = job number, D = num_devices_released
        std::string::size_type first_space = line.find(' ',0);
        std::string::size_type second_space = line.find(' ', first_space+1);
        std::string::size_type third_space = line.find(' ', second_space+1);

        int time = std::stoi(line.substr(first_space+1,second_space-first_space));
        int job_number = std::stoi(line.substr(second_space+3,third_space-second_space));
        int num_devices_released = std::stoi(line.substr(third_space+3,line.length()-third_space));


        while (testOS.time<time) {
          testOS.run();
        }
        std::vector<int> temp_vector;
        temp_vector.push_back(time);
        temp_vector.push_back(job_number);
        temp_vector.push_back(num_devices_released);
        testOS.requests.push_back(temp_vector);

      }
      else if (line[0] == 'D') { //display, print each job, contents of the queues, final state of the system
        std::string::size_type first_space = line.find(' ',0);

        int time = std::stoi(line.substr(first_space+1,line.length()-first_space));


        while (testOS.time<time) {
          testOS.run();
        }
        testOS.display();

      }
      else { //oh dear god something went horribly wrong NOOOO
        std::cout << "Error!" << std::endl;
      }


      //std::cout << testOS.time << std::endl;

    }
    myfile.close();
  }
  else std::cout << "Unable to open file" << std::endl;

  std::cout << "Done" << std::endl;
}
