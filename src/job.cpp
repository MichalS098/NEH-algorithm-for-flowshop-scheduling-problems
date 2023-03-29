#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <queue>
#include "../inc/job.hh"
#include "../inc/helpers.hh"

// void printJobs(const std::vector<Job> &jobs)
// {
//     std::cout << "id, p, w, d" << std::endl;
//     for (int i = 0; i < jobs.size(); i++)
//     {
//         std::cout << jobs[i].getId() << " " << jobs[i].getLength() << " " << jobs[i].getWeight() << " " << jobs[i].getDeadline() << " " << std::endl;
//     }
// }

std::vector<Job> reorderJobs(const std::vector<Job> &jobs, const std::vector<int> &sequence)
{
    std::vector<Job> reordered_jobs;
    for (int i = 0; i < sequence.size(); ++i)
    {
        reordered_jobs.push_back(jobs[sequence[i]]);
    }
    return reordered_jobs;
}

int Cmax(const std::vector<Job> &jobs, const std::vector<int> &sequence = {})
{
    int cmax = 0;
    int number_of_machines = jobs[0].getTasks().size() + 1;
    std::vector<int> machine_times(number_of_machines);
    std::vector<Job> reordered_jobs = sequence.empty() ? jobs : reorderJobs(jobs, sequence);

    for (int i = 0; i < reordered_jobs.size(); ++i)
    {
        std::vector<Task> tasks = reordered_jobs[i].getTasks();
        for (int j = 1; j < number_of_machines; ++j)
        {
            machine_times[j] = std::max(machine_times[j - 1], machine_times[j]) + tasks[j - 1].getDuration();
        }
    }

    return max_of_vector(machine_times);
}

// std::vector<Job> getJobsFromFile(std::string filename, int dataset_number)
// {
//     std::ifstream file(filename);
//     if (!file.is_open())
//     {
//         throw std::runtime_error("Cannot open file " + filename);
//     }

//     std::string line;
//     std::vector<Job> jobs;
//     int p, w, d;
//     bool found_dataset = false;
//     int id = 0;

//     while (std::getline(file, line))
//     {
//         // check if line starts with "data.x:"
//         if (line.find("data." + std::to_string(dataset_number) + ":") == 0)
//         {
//             // read number of jobs
//             std::getline(file, line);
//             int n = std::stoi(line);
//             // read jobs
//             for (int i = 0; i < n; ++i)
//             {
//                 if (!std::getline(file, line))
//                 {
//                     throw std::runtime_error("Unexpected end of file while reading jobs");
//                 }
//                 std::stringstream ss(line);
//                 if (!(ss >> p >> w >> d))
//                 {
//                     throw std::runtime_error("Error reading job data from file");
//                 }
//                 jobs.push_back(Job(id, p, w, d));
//                 id++;
//             }
//             found_dataset = true;
//             break;
//         }
//     }

//     if (!found_dataset)
//     {
//         throw std::runtime_error("Cannot find dataset " + std::to_string(dataset_number) + " in file " + filename);
//     }

//     return jobs;
// }