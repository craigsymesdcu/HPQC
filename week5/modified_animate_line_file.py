import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import pandas as pd
import argparse
from pathlib import Path
import sys

def parse_arguments():
    """Parse command line arguments for the animation script.
    
    Returns:
        argparse.Namespace: Object containing parsed arguments
    """
    parser = argparse.ArgumentParser(
        description="Animate string vibration data from a CSV file",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter
    )
    
    parser.add_argument("input_file", 
                       help="Path to input CSV file containing string position data")
    parser.add_argument("output_file", 
                       help="Base name for output GIF file (without extension)")
    parser.add_argument("--fps", type=int, default=25,
                       help="Frames per second for the animation")
    parser.add_argument("--marker-size", type=int, default=5,
                       help="Size of markers in the animation")
    parser.add_argument("--y-min", type=float, default=-1.1,
                       help="Minimum y-axis value for the plot")
    parser.add_argument("--y-max", type=float, default=1.1,
                       help="Maximum y-axis value for the plot")
    parser.add_argument("--output-dir", default=str(Path.home() / "data"),
                       help="Directory to save output GIF file")
    
    return parser.parse_args()

def generate_output_path(output_dir, basename, extension='gif'):
    """Generate the full output path for the animation file.
    
    Args:
        output_dir (str): Directory to save the file
        basename (str): Base name of the file (without extension)
        extension (str): File extension
        
    Returns:
        str: Full output path
    """
    output_dir = Path(output_dir)
    output_dir.mkdir(parents=True, exist_ok=True)
    return str(output_dir / f"{basename}.{extension}")

def get_data(filename):
    """Read string position data from a CSV file.
    
    Args:
        filename (str): Path to input CSV file
        
    Returns:
        tuple: (data DataFrame, number of positions, number of time steps)
    """
    try:
        data = pd.read_csv(filename, skipinitialspace=True)
    except FileNotFoundError:
        print(f"Error: Input file {filename} not found")
        sys.exit(1)
        
    # First 2 columns are index and time, rest are positions
    num_positions = len(data.columns) - 2
    num_times = len(data)
    
    return data, num_positions, num_times

def extract_position(data, i=0):
    """Extract x and y positions from data for a given time step.
    
    Args:
        data (DataFrame): Input data
        i (int): Time step index
        
    Returns:
        tuple: (x positions, y positions)
    """
    row = data.iloc[i]
    y_positions = np.array(row[2:]).flatten()  # Skip first 2 columns
    x_positions = np.arange(len(row) - 2)      # Generate x positions
    
    return x_positions, y_positions

def configure_animation(frame_count, fps):
    """Set up animation parameters.
    
    Args:
        frame_count (int): Number of frames
        fps (int): Frames per second
        
    Returns:
        tuple: (time steps, interval in ms, fps)
    """
    interval = max(int(1000 / fps), 1)  # Minimum 1ms
    times = np.linspace(0, frame_count/fps, frame_count)
    
    return times, interval, fps

def configure_plot(x_positions, y_positions, y_limits, marker_size):
    """Set up the initial plot for animation.
    
    Args:
        x_positions (array): Initial x positions
        y_positions (array): Initial y positions
        y_limits (tuple): (y_min, y_max) for plot limits
        marker_size (int): Size of markers
        
    Returns:
        tuple: (figure, line object)
    """
    fig, ax = plt.subplots(figsize=(10, 6))
    fig.suptitle('Simulation of Vibrations in a String')
    
    ax.set_ylim(y_limits)
    ax.set_xlabel('Position along string')
    ax.set_ylabel('Displacement')
    
    line, = ax.plot(x_positions, y_positions, "o", 
                    markersize=marker_size, 
                    color="green", 
                    label="Points on string")
    
    ax.legend(handles=[line], loc='upper left')
    
    return fig, line

def animate(time, data, line):
    """Update function for animation.
    
    Args:
        time (int): Current time step
        data (DataFrame): Input data
        line (Line2D): Line object to update
        
    Returns:
        Line2D: Updated line object
    """
    x_pos, y_pos = extract_position(data, time)
    line.set_data(x_pos, y_pos)
    return line,

def main():
    """Main function to run the animation."""
    args = parse_arguments()
    
    # Load and validate data
    data, num_positions, num_times = get_data(args.input_file)
    
    # Set up animation parameters
    times, interval, fps = configure_animation(num_times, args.fps)
    
    # Get initial positions
    x_positions, y_positions = extract_position(data)
    
    # Configure plot
    y_limits = (args.y_min, args.y_max)
    fig, line = configure_plot(x_positions, y_positions, y_limits, args.marker_size)
    
    # Create animation
    ani = animation.FuncAnimation(
        fig, animate, num_times, 
        interval=interval, blit=True,
        fargs=(data, line)
    )
    
    # Save animation
    output_path = generate_output_path(args.output_dir, args.output_file)
    ani.save(filename=output_path, writer="pillow", fps=fps)
    print(f"Animation saved to {output_path}")

if __name__ == "__main__":
    main()