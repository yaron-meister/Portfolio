﻿using GalaSoft.MvvmLight.Command;
using Meisters.Models;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace Meisters.ViewModels
{
    class FloorViewModel : ViewModelBase
    {
        private readonly Employee GENERAL_EMPLOYEE = new Employee("General", false, 100);

        private Employee _selectedActiveEmployee;

        public FloorViewModel()
        {
            Employees.Add(GENERAL_EMPLOYEE);
            SelectActiveEmployee(GENERAL_EMPLOYEE);
        }

        // TODO::YARON - Get it from the model (it gets it through DB)
        public ObservableCollection<Employee> Employees { get; } = new ObservableCollection<Employee>
        {
            new Employee ("May", true, 101),
            new Employee ("Mika", false, 102),
            new Employee ("Dean", false, 103),
            new Employee ("Yaron", true, 104),
        };

        public Employee SelectedActiveEmployee
        { 
            get => _selectedActiveEmployee;
            set
            { 
                _selectedActiveEmployee = value;
                OnPropertyChanged();
            }
        }


        #region Commands

        public ICommand SelectActiveEmployeeCommand => new RelayCommand<Employee>((employee) =>
        {
            if (employee?.Uid != SelectedActiveEmployee.Uid)
            {
                SelectedActiveEmployee.IsSelected = false;
                SelectActiveEmployee(employee);
            }
        });

        #endregion Commands

        private void SelectActiveEmployee(Employee employee)
        {
            SelectedActiveEmployee = employee;
            SelectedActiveEmployee.IsSelected = true;
        }
    }
}
