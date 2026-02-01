#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

const double PI = 3.14159265358979323846;

// Structure représentant un point relais
struct PointRelais {
    string nom;
    double latitude;
    double longitude;
    double distance; // distance par rapport à l'utilisateur
};

// Conversion degrés vers radians
double degToRad(double deg) {
    return deg * PI / 180.0;
}

// Calcul de la distance entre deux points (loi des haversines)
double calculerDistance(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371.0; // rayon de la Terre en km

    double dLat = degToRad(lat2 - lat1);
    double dLon = degToRad(lon2 - lon1);

    double a = sin(dLat / 2) * sin(dLat / 2) + cos(degToRad(lat1)) * cos(degToRad(lat2)) * sin(dLon / 2) * sin(dLon / 2);

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return R * c;
}

int main() {
    double userLat, userLon;

    cout << "=== Localisateur de points relais ===\n\n";
    cout << "Entrez votre latitude : ";
    cin >> userLat;
    cout << "Entrez votre longitude : ";
    cin >> userLon;

    // Liste de points relais fictifs
    vector<PointRelais> points = {
        {"Relais Centre Ville", 48.8566, 2.3522, 0},
        {"Relais Gare", 48.8443, 2.3744, 0},
        {"Relais Nord", 48.9021, 2.3690, 0},
        {"Relais Sud", 48.8156, 2.3622, 0},
        {"Relais Ouest", 48.8499, 2.2876, 0},
        {"Relais Est", 48.8530, 2.4126, 0}
    };

    // Calcul des distances
    for (auto& p : points) {
        p.distance = calculerDistance(userLat, userLon, p.latitude, p.longitude);
    }

    // Tri des points par ordre croissant de distance 
    sort(points.begin(), points.end(),
        [](const PointRelais& a, const PointRelais& b) {
            return a.distance < b.distance;
        });

    cout << "\nLes points relais les plus proches sont :\n\n";

    // Affichage des 5 points les plus proches 
    for (size_t i = 0; i < points.size() && i < 5; i++) {
        cout << i + 1 << ". " << points[i].nom
            << " - " << points[i].distance << " km\n";
    }

    return 0;
}
