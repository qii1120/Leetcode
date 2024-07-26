#include <iostream>

using namespace std;

class Gate
{
    public :
        Gate *input[2] ;
        virtual bool output() = 0 ;
  		void setValue(Gate *, int) ;
        void setValue(bool, int) ;
} ;

class TRUE : public Gate
{
    public :
        virtual bool output() { return 1 ; }
        void setValue(Gate *, int) {}
        void setValue(bool, int) {}
} ;

class FALSE : public Gate
{
    public :
        virtual bool output() { return 0 ; }
        void setValue(Gate *, int) {}
        void setValue(bool, int) {}
} ;

TRUE t ;
FALSE f ;

void Gate::setValue(bool val, int pin)
{
    if(val) this -> input[pin] = &t ;
    else this -> input[pin] = &f ;
}

void Gate::setValue(Gate *gate, int pin) { this -> input[pin] = gate ; }

class NOT : public Gate
{
    public :
        virtual bool output() { return !(this -> input[0] -> output()) ; }
        void setValue(bool val, int pin = 0)
        {
        	if(val) this -> input[0] = &t ;
            else this -> input[0] = &f ;
        }
        void setValue(Gate* gate, int pin = 0) { this -> input[0] = gate ; }
} ;

class NAND : public Gate
{
    public :
        virtual bool output() { return !(this -> input[0] -> output()) || !(this -> input[1] -> output()) ; }
} ;

class NOR : public Gate
{
    public :
        virtual bool output() { return !(this -> input[0] -> output()) && !(this -> input[1] -> output()) ; }
} ;

class AND : public Gate
{
    public :
        AND() : Gate() {
            component[0] = new NOT ;
            component[1] = new NAND ;
            }
        virtual bool output() {

            component[1]->input[0] = this->input[0];
            component[1]->input[1] = this->input[1];
            component[0]->input[0] = component[1];
            return component[0]->output();

        }
    private :
        Gate *component[2] ;
} ;

class OR : public Gate
{
    public :
        OR() : Gate() {
            component[0] = new NOT ;
            component[1] = new NOR ;
        }
        virtual bool output() {

            component[1]->input[0] = this->input[0];
            component[1]->input[1] = this->input[1];
            component[0]->input[0] = component[1];
            return component[0]->output();


        }
    private :
        Gate *component[2] ;
} ;

class XOR : public Gate
{
    public :
        XOR() : Gate() {
            component[0] = new AND;
            component[1] = new AND;
            component[2] = new NOT;
            component[3] = new NOT;
            component[4] = new OR;
        }
        virtual bool output() {

            component[2]->input[0] = this->input[0];  // NOT A
            component[3]->input[0] = this->input[1];  // NOT B

            component[0]->input[0] = this->input[0];
            component[0]->input[1] = component[3];   // A AND NOT B

            component[1]->input[0] = component[2];   // NOT A
            component[1]->input[1] = this->input[1]; // NOT A AND B

            component[4]->input[0] = component[0];   // (A AND NOT B)
            component[4]->input[1] = component[1];   // (NOT A AND B)
            return component[4]->output();           // (A AND NOT B) OR (NOT A AND B)


        }
    private :
        Gate *component[5] ;
} ;

class Adder
{
    public :

        virtual void setValue(bool, int) = 0 ;
        virtual void setValue(Gate *, int) = 0 ;
        virtual Gate *sum() = 0 ;
        virtual Gate *carryOut() = 0 ;
} ;

class OneBitHalfAdder : public Adder
{
    public:
        OneBitHalfAdder() {
            component[0] = new XOR();
            component[1] = new AND();
        }

        virtual void setValue(bool val, int pin) {

            if(val) this -> input[pin] = &t ;
            else this -> input[pin] = &f ;

        }

        virtual void setValue(Gate* gate, int pin) {
            this -> input[pin] = gate ;
        }

        virtual Gate* sum() {
            component[0]->setValue(input[0], 0);
            component[0]->setValue(input[1], 1);
            return component[0];
        }

        virtual Gate* carryOut() {
            component[1]->setValue(input[0], 0);
            component[1]->setValue(input[1], 1);
            return component[1];
        }

    private:
        Gate* component[2];
        Gate* input[2];
};

class OneBitFullAdder : public Adder
{
    public:
        OneBitFullAdder() {
            a[0] = new OneBitHalfAdder();
            a[1] = new OneBitHalfAdder();
            carry = new OR();
        }

        virtual void setValue(bool val, int pin) {
            if (pin < 2) {
                a[0]->setValue(val, pin);
            } else if (pin == 2) {
                a[1]->setValue(val, 1);
            }
            cout<<"setValue"<<pin<<endl;
        }

        virtual void setValue(Gate* gate, int pin) {
            if (pin < 2) {
                a[0]->setValue(gate, pin);
            } else if (pin == 2) {
                a[1]->setValue(gate, 1);
            }
            cout<<"setValue"<<pin<<endl;
        }

        virtual Gate* sum() {
            a[1]->setValue(a[0]->sum(), 0);
            return a[1]->sum();
        }

        virtual Gate* carryOut() {
            a[1]->setValue(a[0]->sum(), 0);
            carry->setValue(a[0]->carryOut(), 0);
            carry->setValue(a[1]->carryOut(), 1);
            return carry;
        }

    private:
        Adder* a[2];
        Gate* carry;

};

int main()
{
    OneBitFullAdder n ;
    n.setValue(&f, 0) ;
    n.setValue(&f, 1) ;
    n.setValue(false, 2) ;
    cout << n.carryOut() -> output() << " " << n.sum() -> output() << endl << endl ;
    n.setValue(&t, 0) ;
    n.setValue(false, 1) ;
    n.setValue(&f, 2) ;
    cout << n.carryOut() -> output() << " " << n.sum() -> output() << endl << endl ;
    n.setValue(false, 0) ;
    n.setValue(true, 1) ;
    n.setValue(&f, 2) ;
    cout << n.carryOut() -> output() << " " << n.sum() -> output() << endl << endl ;
    n.setValue(&t, 0) ;
    n.setValue(true, 1) ;
    n.setValue(false, 2) ;
    cout << n.carryOut() -> output() << " " << n.sum() -> output() << endl << endl ;
    n.setValue(&f, 0) ;
    n.setValue(false, 1) ;
    n.setValue(true, 2) ;
    cout << n.carryOut() -> output() << " " << n.sum() -> output() << endl << endl ;
    n.setValue(true, 0) ;
    n.setValue(&f, 1) ;
    n.setValue(true, 2) ;
    cout << n.carryOut() -> output() << " " << n.sum() -> output() << endl << endl ;
    n.setValue(false, 0) ;
    n.setValue(true, 1) ;
    n.setValue(&t, 2) ;
    cout << n.carryOut() -> output() << " " << n.sum() -> output() << endl << endl ;
    n.setValue(true, 0) ;
    n.setValue(&t, 1) ;
    n.setValue(true, 2) ;
    cout << n.carryOut() -> output() << " " << n.sum() -> output() << endl << endl ;
    Gate *test[1000000] ;
    for(int i = 0 ; i < 1000000 ; i++)
      test[i] = n.carryOut() ;
    for(int i = 0 ; i < 1000000 ; i++)
      test[i] = n.sum() ;
    return 0 ;
}