#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FRAMES 50

void sender(int frames[], int n, int window_size);
void receiver(int frames[], int start, int window_size, int ack[]);

int main() {
    int n, window_size;
    int frames[MAX_FRAMES];

    printf("Sliding Window Protocol Simulation (Selective Repeat ARQ)\n");
    printf("Enter number of frames to send (max %d): ", MAX_FRAMES);
    scanf("%d", &n);

    if(n <= 0 || n > MAX_FRAMES) {
        printf("Invalid number of frames.\n");
        return 0;
    }

    printf("Enter window size: ");
    scanf("%d", &window_size);

    if(window_size <= 0 || window_size > n) {
        printf("Invalid window size.\n");
        return 0;
    }

    // Initialize frames
    for(int i = 0; i < n; i++)
        frames[i] = i;

    sender(frames, n, window_size);

    return 0;
}

void sender(int frames[], int n, int window_size) {
    int base = 0;
    int ack[MAX_FRAMES] = {0};
    char choice;

    srand(time(NULL));

    while(base < n) {
        printf("\nSender window: ");
        for(int i = base; i < base + window_size && i < n; i++)
            printf("[%d] ", frames[i]);

        printf("\nSending frames...\n");
        for(int i = base; i < base + window_size && i < n; i++) {
            if(ack[i] == 0)
                printf("Sent frame: %d\n", frames[i]);
        }

        printf("\nSimulating receiver...\n");
        receiver(frames, base, window_size, ack);

        printf("\nDid any frame get lost? (y/n): ");
        scanf(" %c", &choice);

        if(choice == 'n' || choice == 'N') {
            // All ACKs received
            for(int i = base; i < base + window_size && i < n; i++)
                ack[i] = 1;

            base += window_size;
        } else {
            int lost_frame;
            printf("Enter the frame number that was lost: ");
            scanf("%d", &lost_frame);

            printf("NACK received for frame %d. Retransmitting...\n", lost_frame);
            ack[lost_frame] = 0; // just resend that frame only
        }
    }

    printf("\nAll frames sent successfully using Selective Repeat ARQ!\n");
}

void receiver(int frames[], int start, int window_size, int ack[]) {
    for(int i = start; i < start + window_size; i++) {
        if(ack[i] == 1)
            continue;

        printf("Received frame: %d, sending ACK: %d\n",
               frames[i], frames[i] + 1);
    }
}
