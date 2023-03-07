//
// Created by Annabel Dysinger on 3/7/23.
//

#ifndef PROJECT_03_SPOTIFY_H
#define PROJECT_03_SPOTIFY_H

#include <cassert>   // for assertions
#include <fstream>   // for file i/o
#include <iomanip>   // for manipulating i/o
#include <iostream>
#include <string>
#include <vector>

class Spotify{

private:
    int position, days, peakPosition, peakStreams, totalStreams;
    std::string artistName, songName, peakPositionTimes;
    double topTen;

public:
    // Constructors
    Spotify() {
        //fill in for comparisons and testing
    }

    Spotify(int position, std::string artistName, std::string songName,
            int days, double topTen, int peakPosition, std::string peakPositionTimes,
            int peakStreams, int totalStreams) {
        this->position = position;
        this->artistName = artistName;
        this->songName = songName;
        this->days = days;
        this->topTen = topTen;
        this->peakPosition = peakPosition;
        this->peakPositionTimes = peakPositionTimes;
        this->peakStreams = peakStreams;
        this->totalStreams = totalStreams;
    }
    // Getters
    int getPosition() const {
        return position;
    }

    std::string getArtistName() const {
        return artistName;
    }

    std::string getSongName() const {
        return songName;
    }

    int getDays() const {
        return days;
    }

    double getTopTen() const{
        return topTen;
    }

    int getPeakPosition() const{
        return peakPosition;
    }

    std::string getPeakPositionTimes() const {
        return peakPositionTimes;
    }

    int getPeakStreams() const{
        return peakStreams;
    }
    int getTotalStreams() const{
        return totalStreams;
    }

    //Setters
    void setPosition(int position) {
        this->position = position;
    }

    void setArtistName(std::string artistName) {
        this->artistName = artistName;
    }

    void setSongName(std::string songName) {
        this->songName = songName;
    }

    void setDays(int days) {
        this->days = days;
    }

    void setTopTen(double topTen) {
        this->topTen = topTen;
    }

    void setPeakPosition(int peakPosition) {
        this->peakPosition = peakPosition;
    }

    void setPeakPositionTimes(std::string peakPositionTimes) {
        this->peakPositionTimes = peakPositionTimes;
    }

    void setPeakStreams(int peakStreams){
        this->peakStreams = peakStreams;
    }

    void setTotalStreams(int totalStreams){
        this->totalStreams = totalStreams;
    }

    /**
    * Overload stream insertion operator for pretty printing
    */
    // Overloaded operators
    friend std::ostream& operator << (std::ostream& outs, const Spotify& sObject) {
        outs << std::fixed
             << std::right
             << std::setprecision(4)
             << std::setw(5) << sObject.getPosition()
             << std::setw(25) << sObject.getArtistName()
             << std::left
             << "               "
             << std::setw(40) << sObject.getSongName()
             << "              "
             << std::setw(10) << sObject.getDays()
             << "    "
             << std::setw(20) << sObject.getPeakPosition()
             << std::left
             << std::setw(20) << sObject.getPeakPositionTimes()
             << "    "
             << std::setw(10) << sObject.getPeakStreams()
             << "        "
             << std::setw(10) << sObject.getTotalStreams();
        return outs;

    }

    //object comparisons
    friend bool operator < (const Spotify& lhs, const Spotify& rhs) {
        return lhs.getPosition() < rhs.getPosition();
    }
    friend bool operator > (const Spotify& lhs, const Spotify& rhs) {
        return lhs.getPosition() > rhs.getPosition();
    }
    friend bool operator <= (const Spotify& lhs, const Spotify& rhs) {
        return lhs.getPosition() <= rhs.getPosition();
    }
    friend bool operator >= (const Spotify& lhs, const Spotify& rhs) {
        return lhs.getPosition() >= rhs.getPosition();
    }
    friend bool operator == (const Spotify& lhs, const Spotify& rhs) {
        return lhs.getPosition() == rhs.getPosition();
    }
    friend bool operator != (const Spotify& lhs, const Spotify& rhs) {
        return lhs.getPosition() != rhs.getPosition();
    }
};

/**
* Read data into a vector from the downloaded CSV file.
* Returns true if everything goes well; false otherwise.
* @param filename of file containing data
* @param songs (array)
*/
bool loadFromFile(std::string filename, std::vector<Spotify>& songs){
    std::ifstream fIn;
    fIn.open(filename);

    if (!fIn) {
        // Bad file / could not open
        return false;
    }

    // Get rid of the header line
    if (fIn) {
        std::string header = "";
        getline(fIn, header);
    }

    int counter = 1;

    // We initialize variables to sentinel values --
    // values we *know* will not appear in our data.
    // If any object fields have one of these values, we
    // *know* it was incorrectly set.
    while (fIn && fIn.peek() != EOF) {
        int position = -1;
        std::string artistName = "INVALID";
        std::string songName = "INVALID";
        int days = -1;
        double topTen = -1.0;
        int peakPosition = -1;
        std::string peakPositionTimes = "INVALID";
        int peakStreams = -1;
        int totalStreams = -1;
        char comma = ',';

        fIn >> position;  // Expects an int; reads an int.
        if (position != counter) {
            std::cout << position << " != " << counter << std::endl;
            return false;
        }
        fIn >> comma;
        getline(fIn, artistName, comma);
        getline(fIn, songName, comma);
        fIn >> days;
        fIn >> comma;
        fIn >> topTen;
        fIn >> comma;
        fIn >> peakPosition;
        fIn >> comma;
        getline(fIn, peakPositionTimes, comma);
        fIn >> peakStreams;
        fIn >> comma;
        // checking for ending
        if(fIn.peek() != '\r' && fIn.peek() != '\n'){
            fIn >> totalStreams;
        }

        Spotify stats(position, artistName, songName, days, topTen,
                      peakPosition, peakPositionTimes, peakStreams, totalStreams);
        songs.push_back(stats);
        counter += 1;
    }
    fIn.close();
    return true;
}
/**
* Calculations
*/
void showStats(std::vector<Spotify>& songs){
    int totalTopTen = 0;
    int notTop = 0;
    int taylorSwift = 0;
    for(Spotify& spot : songs){
        double topTenTimes = spot.getTopTen();
        if (topTenTimes != 0.0){
            totalTopTen += 1;
        } else{
            notTop += 1;
        }
    }

    std::cout << std::endl;
    std::cout << "Spotify statistics" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "Number of Songs to Reach Top Ten:" << std::right << std::setw(6)
              << totalTopTen << std::endl;
    std::cout << "Number of Not to Reach Top Ten:" << std::right << std::setw(6)
              << notTop << std::endl;
    std::cout << "==========================" << std::endl;
}
/**
 * This verifies that all fields that should be set are set with
 * good values.
 */
void verifyAllFieldsSet(std::vector<Spotify>& songs) {
    int i = 0;
    for (Spotify& spot : songs) {
        // Position should always = i + 1
        if (spot.getPosition() != i + 1) {
            std::cout << "Bad value for position at record "
                      << i << std::endl;
        }
        std::string artistName = spot.getArtistName();
        if (artistName.compare("INVALID") == 0) {
            std::cout << "Bad value for artist name at record "
                      << i << std::endl;
        }
        std::string songName = spot.getSongName();
        if (songName.compare("INVALID") == 0) {
            std::cout << "Bad value for song name at record "
                      << i << std::endl;
        }
        int days = spot.getDays();
        if (days == -1) {
            std::cout << "Bad value for days at record "
                      << i << std::endl;
        }
        double topTen = spot.getTopTen();
        if(topTen == -1.0){
            std::cout << "Bad value for top ten at record "
                      << i << std::endl;
        }
        int peakPosition = spot.getPeakPosition();
        if(peakPosition == -1){
            std::cout << "Bad value for peak position at record "
                      << i << std::endl;
        }
        std::string peakPositionTimes = spot.getPeakPositionTimes();
        if (peakPositionTimes.compare("INVALID") == 0) {
            std::cout << "Bad value for peak position times at record "
                      << i << std::endl;
        }
        int peakStreams = spot.getPeakStreams();
        if(peakStreams == -1){
            std::cout << "Bad value for peak streams at record "
                      << i << std::endl;
        }
        int totalStreams = spot.getTotalStreams();
        if(totalStreams == -1){
            std::cout << "Bad value for total streams at record "
                      << i << std::endl;
        }
        //"missing" if = -1
        // We'll let these pass silently
        i += 1;
    }
}
/**
 *  object tests.
 * If an assertion fails at runtime, your program will raise an exception.
 */
void spotifyTest(){
    Spotify testObject = Spotify();
    // Testing Getters and setters
    testObject.setPosition(1);
    assert (testObject.getPosition() == 1);
    testObject.setArtistName("Fred");
    assert (testObject.getArtistName() == "Fred");
    testObject.setSongName("Scooby");
    assert (testObject.getSongName() == "Scooby");
    testObject.setDays(1);
    assert (testObject.getDays() == 1);
    testObject.setTopTen(2.0);
    assert (testObject.getTopTen() == 2.0);
    testObject.setPeakPosition(3);
    assert (testObject.getPeakPosition() == 3);
    testObject.setPeakPositionTimes("Velma");
    assert (testObject.getPeakPositionTimes() == "Velma");
    testObject.setPeakStreams(300);
    assert (testObject.getPeakStreams() == 300);
    testObject.setTotalStreams(5);
    assert (testObject.getTotalStreams() == 5);
    // Test initialization
    Spotify testObject2 = Spotify(5, "Anna", "Lucy",
                                  1, 30.0,
                                  5, "Jean", 45, 13);
    assert (testObject2.getPosition() == 5);
    assert (testObject2.getArtistName() == "Anna");
    assert (testObject2.getSongName() == "Lucy");
    assert (testObject2.getDays() == 1);
    assert (testObject2.getTopTen() == 30.0);
    assert (testObject2.getPeakPosition() == 5);
    assert (testObject2.getPeakPositionTimes() == "Jean");
    assert (testObject2.getPeakStreams() == 45);
    assert (testObject2.getTotalStreams() == 13);
}




#endif //PROJECT_03_SPOTIFY_H