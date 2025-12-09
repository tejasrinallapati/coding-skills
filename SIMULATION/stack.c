#include <stdio.h>
#include <string.h>

#define MAX 100   // project level stack size

// Undo and Redo stacks
char undoStack[MAX][1000];
char redoStack[MAX][1000];

int undoTop = -1;
int redoTop = -1;

char currentText[1000] = "";

// Push into undo stack
void pushUndo(char text[]) {
    if (undoTop == MAX - 1) {
        printf("Undo stack full! Cannot save more actions.\n");
        return;
    }
    undoTop++;
    strcpy(undoStack[undoTop], text);
}

// Push into redo stack
void pushRedo(char text[]) {
    if (redoTop == MAX - 1) {
        printf("Redo stack full!\n");
        return;
    }
    redoTop++;
    strcpy(redoStack[redoTop], text);
}

// Pop from undo stack
void popUndo(char text[]) {
    if (undoTop == -1) {
        text[0] = '\0';
        return;
    }
    strcpy(text, undoStack[undoTop]);
    undoTop--;
}

// Pop from redo stack
void popRedo(char text[]) {
    if (redoTop == -1) {
        text[0] = '\0';
        return;
    }
    strcpy(text, redoStack[redoTop]);
    redoTop--;
}

// Clear redo stack when new action is performed
void clearRedo() {
    redoTop = -1;
}

// -----------------------------------------------------

void appendText() {
    char newText[500];

    printf("Enter text to append: ");
    fgets(newText, sizeof(newText), stdin);
    newText[strcspn(newText, "\n")] = '\0';

    // Save current state before changing
    pushUndo(currentText);
    clearRedo();

    strcat(currentText, newText);
    printf("Text updated.\n");
}

void replaceText() {
    char newText[1000];

    printf("Enter new full text: ");
    fgets(newText, sizeof(newText), stdin);
    newText[strcspn(newText, "\n")] = '\0';

    // Save old text in undo
    pushUndo(currentText);
    clearRedo();

    strcpy(currentText, newText);
    printf("Text replaced.\n");
}

void undo() {
    if (undoTop == -1) {
        printf("Nothing to UNDO.\n");
        return;
    }

    // Save current in redo
    pushRedo(currentText);

    char prevText[1000];
    popUndo(prevText);
    strcpy(currentText, prevText);

    printf("Undo successful.\n");
}

void redo() {
    if (redoTop == -1) {
        printf("Nothing to REDO.\n");
        return;
    }

    // Save current to undo
    pushUndo(currentText);

    char redoText[1000];
    popRedo(redoText);
    strcpy(currentText, redoText);

    printf("Redo successful.\n");
}

void showText() {
    printf("\n===== CURRENT TEXT =====\n");
    if (strlen(currentText) == 0)
        printf("[ EMPTY ]\n");
    else
        printf("%s\n", currentText);
    printf("========================\n");
}

// -----------------------------------------------------

int main() {
    int choice;

    printf("=== FULL UNDO-REDO TEXT EDITOR (USING STACK) ===\n");

    while (1) {
        printf("\n1. Append Text");
        printf("\n2. Replace Entire Text");
        printf("\n3. Undo");
        printf("\n4. Redo");
        printf("\n5. Show Text");
        printf("\n6. Exit");
        printf("\nEnter choice: ");

        scanf("%d", &choice);
        getchar();  // flush buffer

        switch (choice) {
            case 1:
                appendText();
                break;

            case 2:
                replaceText();
                break;

            case 3:
                undo();
                break;

            case 4:
                redo();
                break;

            case 5:
                showText();
                break;

            case 6:
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}