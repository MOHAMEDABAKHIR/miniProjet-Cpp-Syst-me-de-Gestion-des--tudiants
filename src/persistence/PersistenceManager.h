#ifndef PERSISTENCE_MANAGER_H
#define PERSISTENCE_MANAGER_H

#include <string>

#include "../services/StudentManager.h"

class PersistenceManager {
public:
    static void save(const StudentManager& manager, const string& path);
    static void load(StudentManager& manager, const string& path);
};

#endif
