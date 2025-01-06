
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Participant {
    char name[100];
    char organization[100];
    char presentation_title[100];
    char contact[100];
    struct Participant* next;
} Participant;

typedef struct ParticipantList {
    Participant* head;
} ParticipantList;

ParticipantList* create_list() {
    ParticipantList* list = (ParticipantList*)malloc(sizeof(ParticipantList));
    list->head = NULL;
    return list;
}

Participant* create_participant(const char* name, const char* organization, const char* presentation_title, const char* contact) {
    Participant* new_participant = (Participant*)malloc(sizeof(Participant));
    strcpy(new_participant->name, name);
    strcpy(new_participant->organization, organization);
    strcpy(new_participant->presentation_title, presentation_title);
    strcpy(new_participant->contact, contact);
    new_participant->next = NULL;
    return new_participant;
}

void add_participant(ParticipantList* list, const char* name, const char* organization, const char* presentation_title, const char* contact) {
    Participant* new_participant = create_participant(name, organization, presentation_title, contact);
    if (!list->head) {
        list->head = new_participant;
    } else {
        Participant* current = list->head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_participant;
    }
}

int update_participant(ParticipantList* list, const char* name, const char* new_name, const char* new_organization, const char* new_presentation_title, const char* new_contact) {
    Participant* current = list->head;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            if (new_name) strcpy(current->name, new_name);
            if (new_organization) strcpy(current->organization, new_organization);
            if (new_presentation_title) strcpy(current->presentation_title, new_presentation_title);
            if (new_contact) strcpy(current->contact, new_contact);
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int delete_participant(ParticipantList* list, const char* name) {
    Participant* current = list->head;
    Participant* previous = NULL;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            if (previous) {
                previous->next = current->next;
            } else {
                list->head = current->next;
            }
            free(current);
            return 1;
        }
        previous = current;
        current = current->next;
    }
    return 0;
}

void search_participant(ParticipantList* list, const char* name, const char* organization) {
    Participant* current = list->head;
    while (current) {
        if ((name && strcmp(current->name, name) == 0) || (organization && strcmp(current->organization, organization) == 0)) {
            printf("Name: %s\nOrganization: %s\nPresentation Title: %s\nContact: %s\n", current->name, current->organization, current->presentation_title, current->contact);
        }
        current = current->next;
    }
}

void display_list(ParticipantList* list) {
    Participant* current = list->head;
    while (current) {
        printf("Name: %s\nOrganization: %s\nPresentation Title: %s\nContact: %s\n\n", current->name, current->organization, current->presentation_title, current->contact);
        current = current->next;
    }
}

void free_list(ParticipantList* list) {
    Participant* current = list->head;
    while (current) {
        Participant* to_free = current;
        current = current->next;
        free(to_free);
    }
    free(list);
}

int main() {
    ParticipantList* list = create_list();

    add_participant(list, "Alice", "Org1", "AI in Healthcare", "alice@example.com");
    add_participant(list, "Bob", "Org2", "Blockchain Basics", "bob@example.com");

    printf("Initial list:\n");
    display_list(list);

    update_participant(list, "Alice", NULL, NULL, NULL, "alice_new@example.com");
    printf("\nAfter update:\n");
    display_list(list);

    delete_participant(list, "Bob");
    printf("\nAfter deletion:\n");
    display_list(list);

    free_list(list);
    return 0;
}
