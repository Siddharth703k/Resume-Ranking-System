# 🧠 AI-Based Resume Ranking System (C++)

A smart **resume screening and candidate ranking system** built in C++ that evaluates candidates based on multiple parameters like skills, experience, education, and certifications using a **weighted scoring algorithm**.

---

## 🚀 Features

### 📊 Intelligent Candidate Evaluation
- Scores candidates based on:
  - Skills (with custom weights)
  - Experience (years)
  - Education (CGPA + degree level)
  - Certifications

### 🎯 Custom Job Requirements
- Define job-specific skills with weights
- Set importance of each category (Skills, Experience, etc.)
- Target job location matching bonus

### 🤖 Smart Ranking Algorithm
- Uses:
  - Weighted scoring system
  - Priority Queue (Max Heap)
  - Tie-breaking using:
    - Experience
    - CGPA

### 📍 Location Awareness
- Candidates get bonus if preferred location matches job location

### 📈 Recommendation System
- STRONG HIRE
- CONSIDER
- REJECT

---

## 🛠️ Tech Stack

- **Language:** C++
- **Concepts Used:**
  - Data Structures (Priority Queue, Hash Maps, Vectors)
  - STL (Standard Template Library)
  - Sorting & Custom Comparators
  - String Processing
  - Basic AI Logic (Rule-based scoring)

---

## 🧠 How It Works

1. Input job requirements:
   - Skills + weights
   - Category weights
   - Target location

2. Input candidate data:
   - Skills
   - Experience
   - CGPA & Degree
   - Certificates
   - Preferred locations

3. System calculates:
   - Skill Score
   - Experience Score
   - Education Score
   - Certificate Score

4. Final Score:
   The final score of each candidate is computed using a weighted sum of all evaluation parameters:

    Total Score =  
    (Skill Score × Skill Weight) +  
    (Experience Score × Experience Weight) +  
    (Education Score × Education Weight) +  
    (Certificate Score × Certificate Weight) +  
    Location Bonus

    Where:
    - Skill Score → Based on matched job skills and their importance
    - Experience Score → Years of experience × 10
    - Education Score → CGPA × 10 (with bonus for higher degrees)
    - Certificate Score → Number of certificates × 10
    - Location Bonus → +15 if preferred location matches job location
