#include <iostream>
#include <string>
#include <cstring>
#include <queue>
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
        finished = false;
    }
    personnel(int _ID, int _n, int _topic[])
    {
        ID = _ID;
        n = _n;
        for (int i = 0; i < _n; i++)
            topic[i] = _topic[i];
        last_ser = -1;
        fini_t = 0;
        finished = false;
    }
    int get_fini_t() { return fini_t; }
    int get_last_ser() { return last_ser; }
    int get_id() { return ID; }
    bool check_finished() { return finished; }
    void ser_req(request &req)
    {
        last_ser = max(req.get_arr_t(), fini_t);
        fini_t = max(req.get_arr_t(), fini_t) + req.get_ser_t();
        req.serve_req();
    }
    void rm_topic(int id)
    {
        if(topic[n-1]==id) topic[n-1]=0;
        for(int i = 0; i < n; i++)
            if(topic[i]==id)
                for(int j=i;j<n-1;j++)
                    topic[j]=topic[j+1];
        n--;
    }
    void serve(int req_n, request (&req)[20]) //, int arr_t)
    {
        int min_arr_t = 1000000, index = -1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < req_n; j++)
            {
                if (topic[i] == req[j].get_id())
                {
                    if(req[j].get_arr_t()==-1)
                    {
                        rm_topic(req[j].get_id());
                        continue;
                    }
                    else if (req[j].get_arr_t() <= fini_t)
                    {
                        ser_req(req[j]);
                        return;
                    }
                    else if (req[j].get_arr_t() < min_arr_t)
                    {
                        min_arr_t = min(min_arr_t, req[j].get_arr_t());
                        index = j;
                    }
                }
            }
        // cout<<index<<endl;
        if (index == -1)
            finished = true;
        else
        {
            ser_req(req[index]);
            return;
        }
    }
    void display()
    {
        cout << ID << " " << n << " " << last_ser << " " << fini_t << " ";
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
    bool finished;
};
class Compare
{
public:
    bool operator()(personnel pl1, personnel pl2)
    {
        return pl1.get_fini_t() > pl2.get_fini_t();
    }
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
        int time = 0; //, l_bound=-1;
        while (1)
        {
            this->display();
            int min_finish_t = 1000000, per_index = -1, last = 1000000;
            for (int i = 0; i < per_n; i++)
            {
                if (personnels[i].check_finished())
                    continue;
                if (personnels[i].get_fini_t() < min_finish_t)
                {
                    min_finish_t = personnels[i].get_fini_t();
                    per_index = i;
                    last = personnels[i].get_last_ser();
                }
                else if (personnels[i].get_fini_t() == min_finish_t && personnels[i].get_last_ser() < last)
                {
                    per_index = i;
                    last = personnels[i].get_last_ser();
                }
            }
            personnels[per_index].serve(req_n, requests);
            time = max(time, personnels[per_index].get_fini_t());
            for (int i = 0; i < req_n; i++)
            {
                if (requests[i].get_arr_t() != -1)
                    break;
                if (requests[i].get_arr_t() == -1 && i == req_n - 1)
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
    int n, x = 1;
    while (cin >> n && n != 0)
    {
        if (x != 1)
            cout << endl;
        senario Senario(n);
        // Senario.display();
        cout << "Scenario " << x++ << ": All requests are serviced within " << Senario.solve() << " minutes.";
    }
    return 0;
}