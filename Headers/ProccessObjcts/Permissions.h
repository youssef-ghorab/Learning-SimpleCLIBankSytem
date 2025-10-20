#pragma once

#include "../ExcepAndErr/ExcepAndErr.h"
#include <vector>

class Permissions
{
public:
    enum class PermissionTypes{NoPermission=0 ,AddClient=1 , DeleteClient=2 , UpdateClient=4 , ClientsList=8 ,FindClient=16 , Transaction=32 , ManageUsers=64 };

private:
    int permissionsHave = (int)PermissionTypes::NoPermission;
    static const int allPermissions = (int)PermissionTypes::AddClient | (int)PermissionTypes::DeleteClient | (int)PermissionTypes::UpdateClient | (int)PermissionTypes::ClientsList | (int)PermissionTypes::FindClient | (int)PermissionTypes::Transaction | (int)PermissionTypes::ManageUsers;

public:
    Permissions(const PermissionTypes p) : permissionsHave((int)p){}

    Permissions(const int p) : permissionsHave(p){}

    Permissions() : permissionsHave((int)PermissionTypes::NoPermission){}

    Permissions(const std::vector<PermissionTypes> &ps) : permissionsHave(permissionsVecToInt(ps)){}

    static int permissionsVecToInt(const std::vector<PermissionTypes> &permissions)
    {
        int permissionsInt = 0;
        for (const PermissionTypes p : permissions) permissionsInt |= (int)p;
        return permissionsInt;
    }

    static std::vector<PermissionTypes> permissiosToVector(const int permissions)
    {
        std::vector<PermissionTypes> permissionVector;

        if (permissions & (int)PermissionTypes::AddClient) permissionVector.push_back(PermissionTypes::AddClient);
        if (permissions & (int)PermissionTypes::DeleteClient) permissionVector.push_back(PermissionTypes::DeleteClient);
        if (permissions & (int)PermissionTypes::UpdateClient) permissionVector.push_back(PermissionTypes::UpdateClient);
        if (permissions & (int)PermissionTypes::ClientsList) permissionVector.push_back(PermissionTypes::ClientsList);
        if (permissions & (int)PermissionTypes::Transaction) permissionVector.push_back(PermissionTypes::Transaction);
        if (permissions & (int)PermissionTypes::ManageUsers) permissionVector.push_back(PermissionTypes::ManageUsers);

        return permissionVector;
    }

    void addPermission(const PermissionTypes permission)
    {
        permissionsHave |= (int)permission;
    }

    bool hasPermission(const PermissionTypes permission) const
    {
        return (permissionsHave & (int)permission) != 0;
    }

    std::vector<PermissionTypes> getHasPermission() const
    {
        return permissiosToVector(permissionsHave);
    }

    void removePermission(const PermissionTypes permission)
    {
        if (!hasPermission(permission)) return;
        permissionsHave &= ~((int)permission);
    }

    void setPermissions(const std::vector<PermissionTypes> &permissions)
    {
        permissionsHave = permissionsVecToInt(permissions);
    }

    static int getAllPermissions()
    {
        return allPermissions;
    }
};