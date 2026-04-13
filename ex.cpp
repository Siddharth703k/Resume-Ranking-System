#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <cmath> 

using namespace std;

// ==========================================
// 1. HELPERS
// ==========================================
string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

bool isPartialMatch(string s1, string s2) {
    s1 = toLower(s1); s2 = toLower(s2);
    if (s1.find(s2) != string::npos || s2.find(s1) != string::npos) return true;
    if ((s1 == "ml" && s2 == "machine learning") || (s2 == "ml" && s1 == "machine learning")) return true;
    return false;
}

// ==========================================
// 2. STRUCTURES
// ==========================================
struct Weights {
    float skillWeight, experienceWeight, educationWeight, certificateWeight;
};

struct Resume {
    string name;
    vector<string> skills;
    vector<string> certificates;
    float experience;
    float cgpa; 
    string degree; 
    vector<string> prefLocations;
    
    float skillScore, certificateScore, experienceScore, educationScore, totalScore;
};

// ==========================================
// 3. SCORING LOGIC
// ==========================================
void processScoring(Resume &r, const unordered_map<string, int>& jobSkills, const Weights &w, string targetLoc) {
    r.skillScore = 0;
    
    for (unordered_map<string, int>::const_iterator it = jobSkills.begin(); it != jobSkills.end(); ++it) {
        string jobSkill = it->first;
        int weight = it->second;
        for (size_t i = 0; i < r.skills.size(); i++) {
            if (isPartialMatch(r.skills[i], jobSkill)) {
                r.skillScore += weight;
                break; 
            }
        }
    }

    float degreeMultiplier = (toLower(r.degree).find("master") != string::npos) ? 1.2f : 1.0f;
    
    float locBonus = 0.0f;
    for (size_t i = 0; i < r.prefLocations.size(); i++) {
        if (toLower(r.prefLocations[i]) == toLower(targetLoc)) {
            locBonus = 15.0f; 
            break; 
        }
    }

    r.certificateScore = (float)r.certificates.size() * 10.0f;
    r.experienceScore = r.experience * 10.0f;
    
    
    r.educationScore = (r.cgpa * 10.0f) * degreeMultiplier;

    r.totalScore = (r.skillScore * w.skillWeight) + 
                   (r.experienceScore * w.experienceWeight) + 
                   (r.educationScore * w.educationWeight) + 
                   (r.certificateScore * w.certificateWeight) + locBonus;
}

// ==========================================
// 4. COMPARATOR
// ==========================================
struct CompareCandidates {
    bool operator()(const Resume &a, const Resume &b) {
        if (std::fabs(a.totalScore - b.totalScore) > 0.01f) {
            return a.totalScore < b.totalScore;
        }
        if (a.experience != b.experience) return a.experience < b.experience;
        return a.cgpa < b.cgpa;
    }
};

// ==========================================
// 5. MAIN
// ==========================================
int main() {
    int n, m;
    cout << "--- Professional Ranking System ---\n";
    cout << "Enter total number of resumes: "; cin >> n;

    Weights w;
    cout << "Set Category Weights [Skills Experience Education Certificates]:\n(Example: 0.4 0.3 0.2 0.1): ";
    cin >> w.skillWeight >> w.experienceWeight >> w.educationWeight >> w.certificateWeight;

    string targetLoc;
    cout << "Target Job Location: "; cin >> targetLoc;

    unordered_map<string, int> jobSkills;
    cout << "Number of required skills for this job: "; cin >> m;
    for(int i=0; i<m; i++) {
        string s; int wt; 
        cout << "  Skill " << i+1 << " and its weight (1-100): "; cin >> s >> wt;
        jobSkills[toLower(s)] = wt;
    }

    priority_queue<Resume, vector<Resume>, CompareCandidates> pq;

    for(int i=0; i<n; i++) {
        Resume r;
        int sCount, cCount, lCount;
        cout << "\n--- Data Entry for Candidate " << i+1 << " ---\nName: "; cin >> r.name;
        cout << "CGPA (0.0-10.0): "; cin >> r.cgpa; 
        cout << "Highest Degree: "; cin >> r.degree;
        cout << "Years of Experience: "; cin >> r.experience;
        
        cout << "How many preferred locations? "; cin >> lCount;
        cout << "  Enter locations: ";
        for(int j=0; j<lCount; j++) { string l; cin >> l; r.prefLocations.push_back(l); }

        cout << "Number of Skills: "; cin >> sCount;
        cout << "  Enter skills: ";
        for(int j=0; j<sCount; j++) { string s; cin >> s; r.skills.push_back(s); }
        
        cout << "Number of Certificates: "; cin >> cCount;
        for(int j=0; j<cCount; j++) { 
            string c; 
            cout << "  Enter Certificate " << j+1 << " Name: "; cin >> c; 
            r.certificates.push_back(c); 
        }

        processScoring(r, jobSkills, w, targetLoc);
        pq.push(r);
    }

    cout << "\n" << setfill('=') << setw(85) << "" << endl;
    cout << left << setw(15) << "RANK/NAME" << setw(10) << "TOTAL" << setw(30) << "BREAKDOWN (S/E/Ed/C)" << "RECOMMENDATION" << endl;
    cout << setfill('-') << setw(85) << "" << endl;

    int rank = 1;
    while(!pq.empty()) {
        Resume r = pq.top(); pq.pop();
        string status = (r.totalScore >= 75) ? "STRONG HIRE" : (r.totalScore >= 45) ? "CONSIDER" : "REJECT";

        cout << left << setw(3) << rank << setw(12) << r.name 
             << setw(10) << fixed << setprecision(1) << r.totalScore 
             << " (" << (int)r.skillScore << "/" << (int)r.experienceScore << "/" << (int)r.educationScore << "/" << (int)r.certificateScore << ")      " 
             << status << endl;
        rank++;
    }
    
    cout << setfill('=') << setw(85) << "" << endl;
    cout << "Key: (S)kills, (E)xperience, (Ed)ucation, (C)ertificates" << endl;
    
    return 0;
}

