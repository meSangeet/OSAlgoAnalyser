#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;


/*--------------- Implementation Of Disc Scheduling Algorithms ---------------------------*/


// Function to perform FCFS scheduling
int fcfs(vector<int>& requests, int head) {
    int total_head_movements = 0;
    for (int i = 0; i < requests.size(); ++i) {
        total_head_movements += abs(head - requests[i]);
        head = requests[i];
    }
    return total_head_movements;
}

// Function to perform SSTF scheduling
int sstf(vector<int>& requests, int head) {
    int total_head_movements = 0;
    while (!requests.empty()) {
        auto min_it = min_element(requests.begin(), requests.end(), [head](int a, int b) {
            return abs(a - head) < abs(b - head);
        });

        total_head_movements += abs(head - *min_it);
        head = *min_it;
        requests.erase(min_it);
    }
    return total_head_movements;
}

// Function to perform SCAN scheduling
int scan(vector<int>& requests, int head, int direction, int disk_size) {
    int total_head_movements = 0;
    int end = (direction == 1) ? disk_size : 0;

    while (!requests.empty()) {
        auto it = (direction == 1) ? min_element(requests.begin(), requests.end()) : max_element(requests.begin(), requests.end());

        if ((direction == 1 && *it >= head) || (direction == -1 && *it <= head)) {
            total_head_movements += abs(head - *it);
            head = *it;
            requests.erase(it);
        } else {
            total_head_movements += abs(head - end);
            head = end;
            direction = -direction; // Change direction
        }
    }
    return total_head_movements;
}

// Function to perform C-SCAN scheduling
// Function to perform SCAN scheduling
int scan(vector<int>& requests, int head, int direction, int disk_size) {
    int total_head_movements = 0;
    int end = (direction == 1) ? disk_size : 0;

    while (!requests.empty()) {
        auto it = (direction == 1) ? min_element(requests.begin(), requests.end()) : max_element(requests.begin(), requests.end());

        if ((direction == 1 && *it >= head) || (direction == -1 && *it <= head)) {
            total_head_movements += abs(head - *it);
            head = *it;
            requests.erase(it);
        } else {
            total_head_movements += abs(head - end);
            head = end;
            direction = -direction; // Change direction
        }
    }
    return total_head_movements;
}


int look(vector<int>& requests, int head, int direct) {
    string direction;
    if(direct==1)
    {direction="right";}
    else{
        direction="left";
    }
    int total_mom = 0;
    int size=requests.size();
    int seek_count = 0; 
    int distance, cur_track; 
    vector<int> left, right; 
    vector<int> seek_sequence; 
  
    for (int i = 0; i < size; i++) { 
        if (requests[i] < head) 
            left.push_back(requests[i]); 
        if (requests[i] > head) 
            right.push_back(requests[i]); 
    } 
  
    
      sort(left.begin(), left.end()); 
      sort(right.begin(), right.end()); 
  
    int run = 2; 
    while (run--) { 
        if (direction == "left") { 
            for (int i = left.size() - 1; i >= 0; i--) { 
                cur_track = left[i]; 
  
                // appending current track to seek sequence 
                seek_sequence.push_back(cur_track); 
  
                // calculate absolute distance 
                distance = abs(cur_track - head); 
  
                // increase the total count 
                total_mom += distance; 
  
                // accessed track is now the new head 
                head = cur_track; 
            } 
            // reversing the direction 
            direction = "right"; 
        } 
        else if (direction == "right") { 
            for (int i = 0; i < right.size(); i++) { 
                cur_track = right[i]; 
                // appending current track to seek sequence 
                seek_sequence.push_back(cur_track); 
  
                // calculate absolute distance 
                distance = abs(cur_track - head); 
  
                // increase the total count 
                total_mom += distance; 
  
                // accessed track is now new head 
                head = cur_track; 
            } 
            // reversing the direction 
            direction = "left"; 
        } 
    } 

    return total_mom;
}

// Function to perform C-LOOK scheduling
int clook(vector<int>& requests, int head) {
    int total = 0;
    int size=requests.size();
    int distance, cur_track;
    vector<int> left, right;
    vector<int> seek_sequence;
 
    // Tracks on the left of the
    // head will be serviced when
    // once the head comes back
    // to the beginning (left end)
    for (int i = 0; i < size; i++) {
        if (requests[i] < head)
            left.push_back(requests[i]);
        if (requests[i] > head)
            right.push_back(requests[i]);
    }
 
    // Sorting left and right vectors
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
 
    // First service the requests
    // on the right side of the head
    for (int i = 0; i < right.size(); i++) {
        cur_track = right[i];
 
        seek_sequence.push_back(cur_track);
 
        distance = abs(cur_track - head);
 
        total += distance;
 
        head = cur_track;
    }
 
    // Once reached the right end
    // jump to the last track that
    // is needed to be serviced in
    // left direction
    total += abs(head - left[0]);
    head = left[0];
 
    // Now service the requests again
    // which are left
    for (int i = 0; i < left.size(); i++) {
        cur_track = left[i];
 
        seek_sequence.push_back(cur_track);
 
        distance = abs(cur_track - head);
 
        total += distance;

        head = cur_track;
    }
 
    return total;
}


int newAlgo(vector<int>&arr)
{
    int prev = 0;
    int tot=0;
    sort(arr.begin(),arr.end());
    for(int i=0;i<arr.size();i++)
    {
        tot+= arr[i]-prev;
        prev = arr[i];
    }
    return tot;
}

void executeDisk() {
    int disk_size,dire;
    int head_position,size;
    cout<<"Welcome to the analysis of DISK SCHEDULING ALGORITHMS!"<<endl;
    cout<<"Enter the disk size i.e. the total no. of tracks disk can have: ";
    cin>>disk_size;
    cout<<"Enter the initial head position of the disk arm: ";
    cin>>head_position;
    cout<<"Enter the number of requests that we need to service: ";
    cin>>size;
    vector<int> requests;
    int a;
    cout<<"Enter the requests/ disk tracks "<<endl;
    for(int i=0;i<size;i++)
    {
        cin>>a;
        requests.push_back(a);
    }
    cout<<"Enter the direction to start with: 1 for right and -1 for left: ";
    cin>>dire;
    
    vector<int>req;
    req=requests;
    // 200 , 50 , {98, 183, 37, 122, 14, 124, 65, 67};

    // FCFS    //643
    cout<<endl<<"Algorithm   Head Moments    Average seek time"<<endl;
    int val1=fcfs(requests, head_position);
    float val12=static_cast<float>(val1)/size; 
    cout << "FCFS:        "<<val1<<"           "<<val12<< endl;

    // SSTF    //205
    requests = req; 
    int val2=sstf(requests, head_position);
    float val22= static_cast<float>(val2)/size;
    cout << "SSTF:        " << val2<<"           "<<val22 << endl;

    // SCAN    //336
    requests = req; 
    int val3= scan(requests, head_position, dire, disk_size);
    float val32=static_cast<float>( val3)/size;
    cout << "SCAN:        " << val3<<"           "<<val32 << endl;

    // C-SCAN  //333
    requests = req; 
    int val4 = cscan(requests, head_position, dire, disk_size);
    float val42= static_cast<float>(val4)/size;
    cout << "C-SCAN:      " << val4<<"           "<<val42 << endl;

    // LOOK   //291
    requests = req; 
    int val5= look(requests, head_position, dire);
    float val52=static_cast<float>(val5)/size;
    cout << "LOOK:        " << val5<<"           "<<val52<< endl;

    // C-LOOK   //321
    requests = req; 
    int val6= clook(requests, head_position);
    float val62=static_cast<float>(val6)/size;
    cout<< "C-LOOK:      " << val6<<"           "<<val62 << endl;
    requests=req;
    int tot= newAlgo(requests);
    cout<<endl<<"With our newly proposed algorithm, we obtain the"<<endl;
    cout<<"total head movements as: "<<tot<<endl;
    cout<<" and the minimum average seek time as "<<static_cast<float>(tot)/size<<endl;

}
