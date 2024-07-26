#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class request
{
public:
    request()
    {
        ID = num = arr_t = ser_t = req_t = cnt = 0;
    }
    request(int _ID, int _num, int _arr_t, int _ser_t, int _req_t)
    {
        ID = _ID;
        num = _num;
        arr_t = _arr_t;
        ser_t = _ser_t;
        req_t = _req_t;
        cnt = 0;
    }
    int get_id() { return ID; }
    int get_arr_t()
    {
        return cnt < num ? arr_t : -1;
    }
    int get_ser_t() { return ser_t; }
    // void update_arr_t(int _arr_t) { arr_t = _arr_t+req_t; cnt++;}
    void serve_req()
    {
        arr_t += req_t;
        cnt++;
    }
    void display()
    {
        cout << ID << " " << num << " " << arr_t << " "
             << " " << ser_t << " " << req_t << " " << cnt << endl;
    }

private:
    int ID;
    int num;
    int arr_t;
    int ser_t;
    int req_t;
    int cnt;
};

class personnel
{
public:
    personnel()
    {
        ID = n = 0;
        memset(&topic, 0, 20);
        last_ser = -1;
        fini_t = 0;
    }
    personnel(int _ID, int _n, int _topic[])
    {
        ID = _ID;
        n = _n;
        for (int i = 0; i < _n; i++)
            topic[i] = _topic[i];
        last_ser = -1;
        fini_t = 0;
    }
    int get_fini_t() { return fini_t; }
    int get_last_ser() { return last_ser; }
    int get_id() { return ID; }
    void update_fini_t(int f) { fini_t = f; }
    void update_last_ser(int l) { last_ser = l; }
    bool able(int id)//, int arr_t)
    {
        for (int i = 0; i < n; i++)
            if (id == topic[i])// && fini_t>=arr_t)
                return true;
        return false;
    }
    void display()
    {
        cout << ID << " " << n << " " << last_ser << " "<<fini_t<<" ";
        for (int i = 0; i < n; i++)
            cout << topic[i] << " ";
        cout << endl;
    }

private:
    int ID;
    int n;
    int topic[20];
    int last_ser;
    int fini_t;
};
class senario
{
public:
    senario() : requests(), req_n(0), personnels(), per_n(0) {}
    senario(int _req_n)
    {
        req_n = _req_n;
        for (int i = 0; i < req_n; i++)
        {
            int id, num, arr_t, ser_t, req_t;
            cin >> id >> num >> arr_t >> ser_t >> req_t;
            requests[i] = request(id, num, arr_t, ser_t, req_t);
        }
        cin >> per_n;
        for (int i = 0; i < per_n; i++)
        {
            int id, num;
            cin >> id >> num;
            int arr[num];
            for (int j = 0; j < num; j++)
                cin >> arr[j];
            personnels[i] = personnel(id, num, arr);
        }
    }
    int solve()
    {
        int time = 0, job_idx = -1, arr_max = 10000000, arr_min = -1, ppl_idx = -1, last = 1000000, min_fini=10000000;
        while (1)
        {
            // this->display();
            for (int i = 0; i < req_n; i++)
            {
                //cout<<"Request arrt "<<requests[i].get_arr_t()<<" "<<arr_max<<" "<<arr_min<<endl;
                if (requests[i].get_arr_t() != -1 && requests[i].get_arr_t() < arr_max )//&& requests[i].get_arr_t() > arr_min)
                {
                    job_idx = i;
                    arr_max = requests[i].get_arr_t();
                }
            }
            for (int i = 0; i < per_n; i++)
            {
                if (personnels[i].able(requests[job_idx].get_id()) && (personnels[i].get_fini_t()<min_fini||(personnels[i].get_fini_t()==min_fini && personnels[i].get_last_ser() < last)))
                {
                    ppl_idx = i;
                    last = personnels[i].get_last_ser();
                    min_fini = personnels[i].get_fini_t();
                }
                //cout<<"per finit: "<<personnels[i].get_fini_t()<<endl;
                // if(personnels[i].able(requests[job_idx].get_id(), 1000000))
                //     min_fini = min(min_fini, personnels[i].get_fini_t());
                //     cout<<"mini: "<<min_fini<<endl;
            }
            // cout<<job_idx+1<<" "<<ppl_idx+1<<endl;
            if (ppl_idx == -1)
            {
            //     //arr_min = requests[job_idx].get_arr_t();
            //     requests[job_idx].update_arr_t(min_fini);
            //     arr_max = min_fini = last = 1000000;
            }
            else
            {
                // cout<<"req arrt: "<<requests[job_idx].get_arr_t()<<endl;
                int tmp = (personnels[ppl_idx].get_fini_t()<requests[job_idx].get_arr_t()?requests[job_idx].get_arr_t():personnels[ppl_idx].get_fini_t());
                requests[job_idx].serve_req();
                personnels[ppl_idx].update_fini_t(tmp+requests[job_idx].get_ser_t());
                personnels[ppl_idx].update_last_ser(tmp);
                // cout<<"req arr t: "<<requests[job_idx].get_arr_t()<<endl;
                time = max(time, personnels[ppl_idx].get_fini_t());
                // cout<<personnels[ppl_idx].get_fini_t()<<" ";
                job_idx = -1, arr_max = 10000000, arr_min = -1, ppl_idx = -1, last = 1000000,  min_fini = 10000000;
            }
            // cout<<time<<endl;
            for (int i = 0; i < req_n; i++)
            {
                if (requests[i].get_arr_t() != -1)
                    break;
                if(requests[i].get_arr_t()==-1 && i==req_n-1)
                    return time;
            }
        }
    }
    void display()
    {
        for (int i = 0; i < req_n; i++)
            requests[i].display();
        for (int i = 0; i < per_n; i++)
            personnels[i].display();
    }

private:
    request requests[20];
    int req_n;
    personnel personnels[5];
    int per_n;
};
int main()
{
    int n, x=1;
    while (cin >> n && n != 0)
    {
        senario Senario(n);
        //Senario.display();
        cout<<"Scenario "<<x++<<": All requests are serviced within "<<Senario.solve()<<" minutes."<<endl;
    }
    return 0;
}