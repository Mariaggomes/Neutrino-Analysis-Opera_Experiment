import streamlit as st
import pandas as pd
import plotly.express as px
import os
import csv
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

st.set_page_config(layout='wide')

st.title('DASHBOARD OPERA')

# Directory where the files are located
directory = 'data/NuMuSample_EmulsionDataset'

# Dictionary to store the DataFrames of each event
dataframes_events = {}

# Inicializar a lista para armazenar os nomes dos eventos
event_names = []

# Iterate over the files in the directory
for file in os.listdir(directory):
    if file.endswith('_Tracks.csv'):
        # Extract the event name from the file title
        event_name = file.split('_Tracks.csv')[0]
        event_names.append(event_name)
        # Read the CSV file and add it to the event dictionary
        file_path = os.path.join(directory, file)
        df_event = pd.read_csv(file_path)
        dataframes_events[event_name] = df_event

# Concatenate all event DataFrames into a single DataFrame
events = pd.concat(dataframes_events.values(), ignore_index=True)

# Dictionary to store the DataFrames of each vertex event
dataframes_events_vertex = {}

# Iterate over the files in the directory and load the DataFrames of the vertices
for file in os.listdir(directory):
    if file.endswith('_Vertex.csv'):
        # Extract the event name from the file title
        event_name = file.split('_Vertex.csv')[0]
        # Read the vertex CSV file and add it to the vertices dictionary
        file_path = os.path.join(directory, file)
        df_vertex = pd.read_csv(file_path)
        dataframes_events_vertex[event_name] = df_vertex

# Concatenate all vertex event DataFrames into a single DataFrame
events_vertex = pd.concat(dataframes_events_vertex.values(), ignore_index=True)

tab1, tab2, tab3, tab4, tab5 = st.tabs(['OPERA Experiment', 'Charmed Hadron', 'Muon Neutrino', 'Muon Neutrino Visualization', 'Classification Model']) 

with tab1:
    st.markdown("**Opera Experiment: Detection of Neutrino Oscillations**")
    st.write(""" 
    The OPERA experiment was developed to achieve the first direct observation of tau neutrinos resulting from the oscillation of muon neutrinos in the long-distance beam from CERN to the Gran Sasso Underground Laboratory, 730 km away. 
    """)
    st.write(""" 
    Neutrino oscillation, proposed by Bruno Pontecorvo in 1957 and confirmed by the Super-Kamiokande experiment, refers to the change in the leptonic flavor of neutrinos as they propagate. This phenomenon indicates that neutrinos have mass, contrary to what the standard model proposed. 
    """)
    st.write(""" 
    OPERA used an innovative approach, combining real-time electronic detectors with the Emulsion Cloud Chamber (ECC) technique. The ECC, composed of lead plates and nuclear emulsion films, allowed for precise detection of neutrino interactions. The OPERA detector consisted of "bricks" made up of 56 lead plates interleaved with emulsion films, totaling 1.25 kilotons, organized into 62 vertical walls. These bricks were followed by layers of plastic scintillators and magnetic spectrometers to measure particle trajectories.  
    """)
    st.write("""
    The OPERA experiment successfully used emulsion films to detect tau neutrinos, extracting detailed information about the topology of neutrino interactions. This included reconstructing the primary interaction vertex and the associated particle tracks. The data collected between 2008 and 2012, with strict selection criteria, resulted in the identification of ten candidate tau neutrino events. These data are available on the CERN Open Data portal and were used to create a three-dimensional visualization of the topologies of the 10 candidate tau neutrino events, as shown in the figure below. The particle tracks are represented in different colors: the tau lepton track in red, the pion (daughter particle) in blue, the photon in white, the pion in gray, the gamma in orange and yellow, and the hadron tracks in green, blue, and pink. The analysis is available on [GitHub](https://github.com/Mariaggomes).
    """)

    column1, column2 = st.columns(2)

    image1 = 'images/neutrinotau.png' 
    image2 = 'images/operatau.png'

    with column1:
        st.image(image1, use_column_width=True)    

    with column2:
        st.image(image2, use_column_width=True)  

with tab2:
    st.markdown("**Opera Experiment: Detection of Charmed Hadrons**")
    st.write("""
    As mentioned earlier, the OPERA experiment aims to directly observe the oscillations of muon neutrinos to tau neutrinos by detecting tau leptons produced in charged-current interactions of tau neutrinos. This method has also been applied in the search for charm hadrons, which exhibit decay patterns similar to tau leptons. In total, fifty candidate events for charm hadron decays have been identified, with their data available on the CERN Open Data portal and analyzed as provided on [GitHub](https://github.com/Mariaggomes).
    """) 

    st.write("""
    The detection process of charm hadrons begins with defining the primary vertex, determined by extrapolating the trajectory to the center of the lead plate immediately above the point where the particle trajectory disappears. This point indicates where the neutrino interacts with the detector, generating new particles. Identifying the primary vertex is crucial for characterizing the produced charm hadrons. Additionally, it is essential to locate the secondary vertex where the produced charm hadron decays into other particles. The distance traveled by the particle before its decay is known as the decay length, whose distribution has been analyzed.
    """) 

    st.write("""
    To confirm the presence of charm particles, the experiment searches for extra tracks. These tracks traverse at least three emulsion films and have an impact parameter relative to the primary vertex of less than 300 μm (or 500 μm, depending on the z-distance relative to the vertex). The distribution of impact parameters of the daughter particles resulting from the decay of charm hadrons has also been analyzed. These additional tracks are important for confirming the presence of charm particles and for distinguishing the events of interest from background noise.
    """) 

    # Dictionaries to store the data
    primary_vertices = {}
    secondary_vertices = {}
    daughter_track_line_sets = {}

    # Functions for reading files
    def read_vertex_file(data_file_path):
        event_id = int(os.path.basename(data_file_path).split("_")[0])
        with open(data_file_path, 'r') as file:
            reader = csv.reader(file)
            next(reader)  
            primary_vertices[event_id] = list(map(float, next(reader)[1:4]))
            secondary_vertices[event_id] = list(map(float, next(reader)[1:4]))

    def read_track_lines_file(data_file_path):
        event_id = int(os.path.basename(data_file_path).split("_")[0])
        with open(data_file_path, 'r') as file:
            reader = csv.reader(file)
            next(reader)  
            daughter_track_line_sets[event_id] = [list(map(float, row[1:])) for row in reader if int(row[0]) == 10]

    # Searching for data files
    data_dir_name = "data/CharmSample_EmulsionDataset"
    for data_file in os.listdir(data_dir_name):
        data_file_path = os.path.join(data_dir_name, data_file)
        if data_file.endswith("_Vertices.csv"):
            read_vertex_file(data_file_path)
        elif data_file.endswith("_TrackLines.csv"):
            read_track_lines_file(data_file_path)

    # Filling and plotting histograms
    flight_lengths = [np.linalg.norm(np.array(primary_vertices[event_id]) - np.array(secondary_vertices[event_id])) for event_id in primary_vertices if event_id in secondary_vertices]
    fig1, ax1 = plt.subplots()
    plt.hist(flight_lengths, bins=9, range=(0, 5300), color='blue', alpha=0.7)
    plt.title("Flight lengths of charmed hadrons")
    plt.xlabel("Flight length (#mum)")
    plt.ylabel("Nb of events")

    column1, column2 = st.columns(2)
    
    with column1:
        st.pyplot(fig1)

   # Plotting the impact parameter histogram
    track_ips = [np.linalg.norm(np.cross(np.array(track_line[3:]) - np.array(track_line[:3]), np.array(track_line[:3]) - np.array(primary_vertices[event_id]))) / np.linalg.norm(np.array(track_line[3:]) - np.array(track_line[:3])) for event_id in daughter_track_line_sets for track_line in daughter_track_line_sets[event_id]]    
    fig2, ax2 = plt.subplots()    
    plt.hist(track_ips, bins=10, range=(0, 500), color='red', alpha=0.7)
    plt.title("Impact parameters of tracks of daughter particles")
    plt.xlabel("IP (#mum)")
    plt.ylabel("Nb of tracks")

   
    with column2:
        st.pyplot(fig2)  

with tab3:  

    st.markdown("**Opera Experiment: Detection of Muon Neutrino**")
    st.write("""
    The OPERA experiment collected data from 817 muon neutrino interactions with a lead target, which were made available on the CERN open data portal and analyzed as detailed at [GitHub](https://github.com/Mariaggomes). These interactions involve charged-current interactions of muon neutrinos, resulting in the reconstruction of a muon in the final state. During these interactions, various hadrons are produced when muon neutrinos interact with nucleons in the lead target.
    """) 

    st.write("""
    The dataset provides detailed information about the neutrino interaction vertices, which denote the origin points of each event. These vertices mark the initial location where the neutrino interacts with the detector, leading to the creation of other particles.
    """) 

    st.write("""
    Additionally, the dataset includes emulsion tracks resulting from these interactions, which trace the trajectories of the particles generated during the event. These tracks typically form due to the neutrino's interaction with the material in the detector and represent the individual trajectories of detected particles in a specific event. Therefore, track multiplicity is an essential measure for understanding the kinematics of the produced particles, identifying interaction patterns, and validating theoretical models of collision processes. Consequently, the tracks associated with the primary vertex of the muon neutrino interaction were identified and recorded in a histogram.
    """) 

    st.write("""
    Each emulsion track is defined by its starting point, a 3D point near the vertex, and two slopes represented by the tangents of the angles relative to the Z-axis in the XZ and YZ views. From this, the angles of the muon trajectories were obtained using the equation θ = tan⁻¹(s), where θ represents the angle of the muon trajectory in radians, and s is the slope.
    """) 

    #Show dataframe events
    column1, column2 = st.columns(2)

    with column1:
        
        bin_edges = range(events_vertex['mult'].min(), events_vertex['mult'].max() + 1, 1)  # Definindo limites dos bins de 1 a max(mult)

       
        fig, ax = plt.subplots()
        ax.hist(events_vertex['mult'], bins=bin_edges, color='blue', alpha=0.7)
        ax.set_xlabel('Multiplicity')
        ax.set_ylabel('Number of Entries')
        ax.set_title('Track Multiplicity')

        st.pyplot(fig, use_container_width=True)

    with column2:
        
        image = 'images/muon_angles.png' 
        st.image(image, use_column_width=True)

with tab4:  

    st.write("""By visualizing the interaction vertices and track in a 3D context, this analysis aims to provide a comprehensive understanding of the physical events captured by the OPERA detector.""")
    column1, column2 = st.columns(2)

    # Check if the event list is not empty
    if event_names:

        with column1:
        # Event number selection input
            selected_event = st.selectbox("**Select the Event Number:**", event_names)

       # Display the selected event number
            st.write(f"Selected event number: {selected_event}")

        # Display the selected event data 
        if selected_event in dataframes_events:
            df_event = dataframes_events[selected_event]
        
        if selected_event in dataframes_events_vertex:
            # Get the vertex DataFrame corresponding to the selected event
            event_vertex = dataframes_events_vertex[selected_event]
            with column1:
                st.write("""**Event Vertices**""")
                st.dataframe(event_vertex)
                st.write("""**Event Tracks**""")
                st.dataframe(df_event)
                st.write("""The column trType represents the type of track detected, with each number corresponding to a specific type of particle recorded by the detector: 1 - muon; 2 - hadron; 3 - electron; 4 - black; 5 - back black; 6 - gray; 7 - back gray.""")

            # Creation of the 3D plot
            fig = plt.figure()
            ax = fig.add_subplot(111, projection='3d')

            colors = {
                1: ('red', 'Muon'), 
                2: ('aqua', 'Hadron'), 
                3: ('slategray', 'Electron'), 
                4: ('green', 'Black'), 
                5: ('gold', 'Back Black'), 
                6: ('teal', 'Gray'), 
                7: ('purple', 'Back Gray')
            }  


            plotted_labels = set()

            # Plot particle trajectories
            for index, row in df_event.iterrows():
                x, y, z = row['posX'], row['posY'], row['posZ']
                trType = row['trType']
                
                
                if trType in colors:
                    color, label = colors[trType]
                    if label not in plotted_labels:
                        ax.plot([x], [y], [z], marker='o', color=color, label=label)  # Adicionar rótulo
                        plotted_labels.add(label)
                    else:
                        ax.plot([x], [y], [z], marker='o', color=color)
                else:
                    ax.plot([x], [y], [z], marker='o')  
                # Add dashed gray line connecting vertex to track
                if not event_vertex.empty:
                    x_vertex, y_vertex, z_vertex = event_vertex.iloc[0][['posX', 'posY', 'posZ']]
                    ax.plot([x_vertex, x], [y_vertex, y], [z_vertex, z], linestyle='--', color='gray')
            
            # Plot vertex point
            if not event_vertex.empty:
                x_vertex, y_vertex, z_vertex = event_vertex.iloc[0][['posX', 'posY', 'posZ']]
                ax.scatter(x_vertex, y_vertex, z_vertex, marker='o', color='black', label='Vertex Point')

            ax.set_xlabel('X')
            ax.set_ylabel('Y')
            ax.set_zlabel('Z')

          
            ax.set_title('Visualization of Particle Trajectories')
            ax.legend()
            
            with column2:
                st.pyplot(fig, use_container_width=True)
    else:
        st.write("Nenhum evento disponível para seleção.")

with tab5:
    st.write("""Given that each event includes a reconstructed muon in the final state, the analysis also focused on developing a machine learning algorithm. This algorithm aimed to create a binary classifier specifically designed to identify muons within the dataset, enhancing our ability to interpret and analyze the muon neutrino interactions recorded by the OPERA detector. The detailed development of the algorithm can be found on [GitHub](https://github.com/Mariaggomes). """)

    # Turn the problem into a binary problem  (one vs all)
    events['trType'] = events['trType'].apply(lambda x: 1 if x == 1 else 0)

    column1, column2 = st.columns(2)
    with column1:
        st.metric('Muon', round(events['trType'].value_counts()[1]/len(events) * 100,2), '% of the dataset')
    with column2:
        st.metric('No Muon', round(events['trType'].value_counts().iloc[0] / len(events) * 100, 2), '% of the dataset')

    import streamlit as st


    st.write("#### Data Pre-processing")
    st.write(
        "During pre-processing, the SMOTE technique was applied to balance the classes by generating synthetic examples of the minority class. "
        "Although this improved data balance, challenges remain in generalizing to unseen data."
    )

    # Decision Tree
    st.subheader("Model 1: Decision Tree")
    st.write(
        "##### Performance\n"
        "Excellent at identifying muons (class 1), with good recall and acceptable precision. "
        "Out of 744 muon events, 90 were incorrectly classified as non-muons, resulting in an error rate of approximately 12.10%, highlighting limitations in classification precision.\n"
        "##### Challenges\n"
        "With an AUC of 0.662 and lower ability to identify non-muon events (class 0), out of 744 non-muon events, 425 were incorrectly classified as muons. Post-processing is needed to reduce false positives."
    )

    # Random Forest
    st.subheader("Model 2: Random Forest")
    st.write(
        "##### Performance\n"
        "Reasonable performance with slightly higher precision and recall compared to the decision tree. AUC of 0.737.\n"
        "##### Challenges\n"
        "A decrease in precision and recall on the test set suggests overfitting. Improvement is needed for the recall of class 1, which is currently 0.58."
    )

    # Model Ensemble
    st.subheader("Model 3: Ensemble (Decision Tree + Random Forest)")
    st.write(
        "##### Performance\n"
        "Balanced precision and recall for both classes, with an F1-score of 0.66 for class 1 and 0.67 for class 0. AUC of 0.727.\n"
        "##### Challenges\n"
        "There is a need to improve class distinction and recall for class 1. Additionally, there is a decrease in precision and recall on the test set, indicating overfitting."
    )

    st.header("Conclusion")
    st.write(
        "##### Decision Tree\n"
        "Shows the best performance in identifying muons but requires post-processing to address false positives.\n"
        "##### Random Forest\n"
        "Exhibits good overall performance but may be less effective at identifying muons compared to the decision tree.\n"
        "##### Model Ensemble\n"
        "Provides a balance between individual approaches but still needs improvement in class distinction.\n"
    )
    st.write("All models have been registered in MLflow to facilitate future improvements and retraining.")

    
    image = 'images/confusion_matrix_comparison.png' 
    st.image(image, use_column_width=True)
    
    image1 = 'images/model_comparison_metrics.png' 
    st.image(image1, use_column_width=100)


