#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <Aclapi.h>
#include "permissions.h"

void change_permissions(const char *path, const char *perm) {
    // Open the file to get its security information
    HANDLE hFile = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        perror("Failed to open file");
        return;
    }

    // Get current security information (including DACL)
    PSECURITY_DESCRIPTOR pSD = NULL;
    PACL pOldDACL = NULL, pNewDACL = NULL;
    if (GetSecurityInfo(hFile, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, &pOldDACL, NULL, &pSD) != ERROR_SUCCESS) {
        printf("Failed to get security information\n");
        CloseHandle(hFile);
        return;
    }

    // Prepare the EXPLICIT_ACCESS structure to grant permissions
    EXPLICIT_ACCESS ea;
    ZeroMemory(&ea, sizeof(EXPLICIT_ACCESS));

    // Example: Allow everyone to read and write
    ea.grfAccessPermissions = GENERIC_READ | GENERIC_WRITE;
    ea.grfAccessMode = GRANT_ACCESS;
    ea.grfInheritance = NO_INHERITANCE;
    ea.Trustee.TrusteeForm = TRUSTEE_IS_NAME;
    char buffer[256];
    strcpy(buffer, "Everyone");
    ea.Trustee.ptstrName = buffer;  // Use LPCSTR for constant string literals
  // Change this to another user/group as needed

    // Set the new ACL with the updated access permissions
    if (SetEntriesInAcl(1, &ea, pOldDACL, &pNewDACL) != ERROR_SUCCESS) {
        printf("Failed to set ACL entries\n");
        LocalFree(pSD); // Don't forget to free security descriptor
        CloseHandle(hFile);
        return;
    }

    // Apply the new DACL to the file's security descriptor
    if (SetFileSecurity(path, DACL_SECURITY_INFORMATION, pSD) == 0) {
        printf("Failed to set file security\n");
    } else {
        printf("Permissions changed successfully.\n");
    }

    // Clean up
    LocalFree(pSD);
    CloseHandle(hFile);
}
