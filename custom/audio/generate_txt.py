import os

# Path to the directory containing subdirectories and audio files
parent_directory = "./"

# Function to create the text file with the list of audio files
def create_file_list(parent_directory):
    # Iterate through subdirectories in the parent directory
    for sub_directory in os.listdir(parent_directory):
        print(sub_directory)
        sub_directory_path = os.path.join(parent_directory, sub_directory)
        # Check if the path corresponds to a directory
        if os.path.isdir(sub_directory_path):
            # List of audio files in the subdirectory
            audio_files = [file for file in os.listdir(sub_directory_path) if file.endswith('.mp3')]
            # Create the path for the text file
            text_file_path = sub_directory_path +".txt"
            # Write the list of audio files to the text file
            with open(text_file_path, 'w') as f:
                for audio_file in audio_files:
                    f.write(audio_file + '\n')

# Call the function to create the text files with the lists of audio files
create_file_list(parent_directory)
