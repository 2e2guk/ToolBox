/*
큰 수 덧셈 : string bigAdd(string num1, string num2)
큰 수 뺄셈: string bigSubtract(string num1, string num2)
큰 수 곱셈: string bigMultiply(const string &num1, const string &num2)
큰 수 나눗셈: pair<string, string> bigDivide(const string &A, const string &B)

시간복잡도
큰 수 덧셈 : O(n)
큰 수 뺄셈: O(n)
큰 수 곱셈: O(nlogn)
큰 수 나눗셈: O(n^2)

BOJ예제
큰 수 덧셈 : 15740 (-10^10000 < A,B < 10^10000) (0ms)
큰 수 뺄셈: O(n)
큰 수 곱셈: 15576 (208ms) (0 ≤ A,B < 10^300000)
큰 수 나눗셈: 16428 O(n^2) (-10^10000 ≤ A ≤ 10^10000 && -10^18 ≤ B ≤ 10^18)
*/

#include <bits/stdc++.h>
using namespace std;
string bigSubtract(string num1, string num2);
// Helper function to remove leading zeros
string removeLeadingZeros(const string &str) {
    size_t i = 0;
    while (i < str.size() - 1 && str[i] == '0')
        i++;
    return str.substr(i);
}

// Helper function to compare two positive numbers
// Returns:
// -1 if num1 < num2
// 0 if num1 == num2
// 1 if num1 > num2
int compare(const string &a, const string &b) {
    string A = removeLeadingZeros(a);
    string B = removeLeadingZeros(b);
    if (A.size() < B.size())
        return -1;
    if (A.size() > B.size())
        return 1;
    for (size_t i = 0; i < A.size(); ++i) {
        if (A[i] < B[i])
            return -1;
        if (A[i] > B[i])
            return 1;
    }
    return 0;
}

// Helper function to add two positive numbers represented as strings
string addPositive(const string &num1, const string &num2) {
    string result;
    int carry = 0;
    int i = (int)num1.size() - 1;
    int j = (int)num2.size() - 1;
    while (i >= 0 || j >= 0 || carry) {
        int digitSum = carry;
        if (i >= 0)
            digitSum += num1[i--] - '0';
        if (j >= 0)
            digitSum += num2[j--] - '0';
        carry = digitSum / 10;
        result.push_back(digitSum % 10 + '0');
    }
    reverse(result.begin(), result.end());
    return result;
}

// Helper function to subtract two positive numbers represented as strings (num1 - num2)
// Assumes num1 >= num2
string subtractPositive(const string &num1, const string &num2) {
    string result;
    int i = (int)num1.size() - 1;
    int j = (int)num2.size() - 1;
    int borrow = 0;
    while (i >= 0) {
        int digit1 = num1[i] - '0' - borrow;
        int digit2 = (j >= 0) ? num2[j] - '0' : 0;
        if (digit1 < digit2) {
            digit1 += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.push_back(digit1 - digit2 + '0');
        i--;
        j--;
    }
    reverse(result.begin(), result.end());
    return removeLeadingZeros(result);
}

// Function to add two big integers represented as strings
string bigAdd(string num1, string num2) {
    // Remove leading zeros
    num1 = removeLeadingZeros(num1);
    num2 = removeLeadingZeros(num2);

    // Check for negative signs
    bool negative1 = false, negative2 = false;
    if (num1[0] == '-') {
        negative1 = true;
        num1 = num1.substr(1);
    }
    if (num2[0] == '-') {
        negative2 = true;
        num2 = num2.substr(1);
    }

    string result;
    if (!negative1 && !negative2) {
        // Both positive
        result = addPositive(num1, num2);
    } else if (negative1 && negative2) {
        // Both negative
        result = "-" + addPositive(num1, num2);
    } else if (negative1 && !negative2) {
        // num1 negative, num2 positive => num2 - num1
        int cmp = compare(num1, num2);
        if (cmp == 0) {
            result = "0";
        } else if (cmp < 0) {
            result = subtractPositive(num2, num1);
        } else {
            result = "-" + subtractPositive(num1, num2);
        }
    } else { // !negative1 && negative2
        // num1 positive, num2 negative => num1 - num2
        int cmp = compare(num1, num2);
        if (cmp == 0) {
            result = "0";
        } else if (cmp > 0) {
            result = subtractPositive(num1, num2);
        } else {
            result = "-" + subtractPositive(num2, num1);
        }
    }
    return result;
}

// Function to subtract two big integers represented as strings (num1 - num2)
string bigSubtract(string num1, string num2) {
    // Remove leading zeros
    num1 = removeLeadingZeros(num1);
    num2 = removeLeadingZeros(num2);

    // Check for negative signs
    bool negative1 = false, negative2 = false;
    if (num1[0] == '-') {
        negative1 = true;
        num1 = num1.substr(1);
    }
    if (num2[0] == '-') {
        negative2 = true;
        num2 = num2.substr(1);
    }

    string result;
    if (!negative1 && !negative2) {
        // Both positive: num1 - num2
        int cmp = compare(num1, num2);
        if (cmp == 0) {
            result = "0";
        } else if (cmp > 0) {
            result = subtractPositive(num1, num2);
        } else {
            result = "-" + subtractPositive(num2, num1);
        }
    } else if (negative1 && negative2) {
        // Both negative: (-num1) - (-num2) = num2 - num1
        int cmp = compare(num1, num2);
        if (cmp == 0) {
            result = "0";
        } else if (cmp < 0) {
            result = subtractPositive(num2, num1);
        } else {
            result = "-" + subtractPositive(num1, num2);
        }
    } else if (negative1 && !negative2) {
        // num1 negative, num2 positive: (-num1) - num2 = -(num1 + num2)
        result = "-" + addPositive(num1, num2);
    } else { // !negative1 && negative2
        // num1 positive, num2 negative: num1 - (-num2) = num1 + num2
        result = addPositive(num1, num2);
    }
    return result;
}

const double PI = acos(-1);
typedef complex<double> cpx;
typedef long long ll;

void FFT(vector<cpx> &v, bool inv) {
    ll S = v.size(); // ll 타입으로 선언

    for(ll i=1, j=0; i<S; i++) {
        ll bit = S >> 1;
        while(j >= bit) {
            j -= bit;
            bit >>= 1;
        }
        j += bit;
        if(i < j) swap(v[i], v[j]);
    }

    for(ll k=1; k<S; k<<=1) {
        double angle = inv ? PI/k : -PI/k;
        cpx dir(cos(angle), sin(angle));
        for(ll i=0; i<S; i+=(k<<1)) {
            cpx unit(1, 0);
            for(ll j=0; j<k; j++) {
                cpx a = v[i+j], b = v[i+j+k] * unit;
                v[i+j] = a + b;
                v[i+j+k] = a - b;
                unit *= dir;
            }
        }
    }

    if(inv) {
        for(ll i=0; i<S; i++) v[i] /= S;
    }
}
/*
input : a => A's Coefficient, b => B's Coefficient
output : A * B
*/
vector<cpx> mul(vector<cpx> &v, vector<cpx> &u) {
    ll S = 1;
    while(S < max(v.size(), u.size())) S <<= 1;
    S <<= 1; // 벡터의 길이를 조정하여 곱셈을 위한 충분한 길이를 확보

    v.resize(S); FFT(v, false);
    u.resize(S); FFT(u, false);

    vector<cpx> w(S);
    for(ll i=0; i<S; i++) w[i] = v[i] * u[i];

    FFT(w, true); // 역 FFT 수행
    return w;
}

// 큰 수 곱셈을 처리하는 함수
string bigMultiply(const string &num1, const string &num2) {
    vector<cpx> a(num1.size()), b(num2.size());

    // 문자열을 각 자리 수로 변환하여 벡터에 저장 (뒤에서부터)
    for (ll i = 0; i < num1.size(); i++)
        a[i] = num1[num1.size() - i - 1] - '0';
    for (ll i = 0; i < num2.size(); i++)
        b[i] = num2[num2.size() - i - 1] - '0';

    // FFT 기반 곱셈 수행
    vector<cpx> result = mul(a, b);

    // 자리수 처리
    vector<ll> res(result.size());
    ll carry = 0;
    for (ll i = 0; i < result.size(); i++) {
        res[i] = (ll)(result[i].real() + 0.5) + carry;
        carry = res[i] / 10;
        res[i] %= 10;
    }

    // 앞자리에서 0 제거
    while (res.size() > 1 && res.back() == 0) res.pop_back();

    // 결과를 문자열로 변환
    string product = "";
    for (ll i = res.size() - 1; i >= 0; i--) product += to_string(res[i]);

    return product;
}

// 두 매우 큰 수를 나누는 함수
// Multiply a positive big integer by a single-digit integer
string bigMultiplyDigit(const string &a, char digit) {
    if (digit == '0' || a == "0")
        return "0";
    int d = digit - '0';
    string result;
    int carry = 0;
    for (int i = (int)a.size() - 1; i >= 0; --i) {
        int prod = (a[i] - '0') * d + carry;
        carry = prod / 10;
        result.push_back(prod % 10 + '0');
    }
    if (carry)
        result.push_back(carry + '0');
    reverse(result.begin(), result.end());
    return removeLeadingZeros(result);
}

// Multiply a positive big integer by 10
string bigMultiplyBy10(const string &a) {
    return a + "0";
}

// Division of positive big integers
pair<string, string> bigDividePositive(const string &a, const string &b) {
    string A = removeLeadingZeros(a);
    string B = removeLeadingZeros(b);
    if (compare(A, B) < 0)
        return make_pair("0", A);
    string quotient;
    string remainder;
    size_t idx = 0;
    remainder = "";
    while (idx < A.size()) {
        remainder += A[idx++];
        remainder = removeLeadingZeros(remainder);
        // Binary search to find the quotient digit
        int low = 0, high = 9, q_digit = 0;
        while (low <= high) {
            int mid = (low + high) / 2;
            string temp = bigMultiplyDigit(B, mid + '0');
            if (compare(temp, remainder) <= 0) {
                q_digit = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        quotient += q_digit + '0';
        string temp = bigMultiplyDigit(B, q_digit + '0');
        remainder = bigSubtract(remainder, temp);
    }
    quotient = removeLeadingZeros(quotient);
    remainder = removeLeadingZeros(remainder);
    return make_pair(quotient, remainder);
}

// Main function to perform big integer division
pair<string, string> bigDivide(const string &A, const string &B) {
    // Handle sign
    bool negativeA = false, negativeB = false;
    string a = A, b = B;
    if (A[0] == '-') {
        negativeA = true;
        a = A.substr(1);
    }
    if (B[0] == '-') {
        negativeB = true;
        b = B.substr(1);
    }
    if (b == "0")
        throw invalid_argument("Division by zero");

    pair<string, string> result = bigDividePositive(a, b);
    string q = result.first;
    string r = result.second;

    // Adjust quotient and remainder if A was negative
    if (negativeA && r != "0") {
        q = bigAdd(q, "1");
        r = bigSubtract(b, r);
    }
    // Apply sign to quotient
    if (q != "0" && negativeA != negativeB)
        q = "-" + q;

    return make_pair(q, r);
}

int main(){

    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    string a,b,c;
    cin>>a>>b;
    /*
    c = bigAdd(a,b);
    c = bigSubtract(a,b);
    c = bigMultiply(a,b);
    cout<<c;
    */
   
    /*
    pair<string, string> result = bigDivide(a, b);
    cout<<result.first<<" "<<result.second<<endl;
    */
    
    return 0;
}