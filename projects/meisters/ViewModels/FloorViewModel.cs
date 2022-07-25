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
        private string _searchText = string.Empty;
        private bool _isActivatingEmp = false;
        private ObservableCollection<Employee> _activeEmployees = new ObservableCollection<Employee>();
        private IEnumerable<Employee> _filteredInactiveEmployees = new ObservableCollection<Employee>();
        private ObservableCollection<Employee> _inactiveEmployees = new ObservableCollection<Employee>()
        {
            // TODO::YARON - Get it from the model (it gets it through DB)
            new Employee ("May", true, 101),
            new Employee ("Mika", false, 102),
            new Employee ("Dean", false, 103),
            new Employee ("Yaron", true, 104),
        };

        public FloorViewModel()
        {
            ActiveEmployees.Add(GENERAL_EMPLOYEE);
            SelectActiveEmployee(GENERAL_EMPLOYEE);
        }


        public Employee SelectedActiveEmployee
        {
            get => _selectedActiveEmployee;
            set
            {
                _selectedActiveEmployee = value;
                OnPropertyChanged();
            }
        }

        public string SearchText
        {
            get => _searchText;
            set
            {
                _searchText = value;
                OnPropertyChanged();
                FilterInactiveEmployees();
            }
        }

        public bool IsActivatingEmp
        {
            get => _isActivatingEmp;
            set
            {
                _isActivatingEmp = value;
                OnPropertyChanged();
            }
        }

        public ObservableCollection<Employee> ActiveEmployees
        {
            get => _activeEmployees;
            set
            {
                _activeEmployees = value;
                OnPropertyChanged();
            }
        }

        public ObservableCollection<Employee> InactiveEmployees
        {
            get => _inactiveEmployees;
            set
            {
                _inactiveEmployees = value;
                OnPropertyChanged();
            }
        }

        public IEnumerable<Employee> FilteredInactiveEmployees
        {
            get => _filteredInactiveEmployees;
            set
            {
                _filteredInactiveEmployees = value;
                OnPropertyChanged();
            }
        }

        #region Commands

        public ICommand SelectActiveEmployeeCommand => new RelayCommand<Employee>((employee) =>
        {
            if (employee?.Uid != SelectedActiveEmployee?.Uid)
            {
                if (SelectedActiveEmployee != null)
                {
                    SelectedActiveEmployee.IsSelected = false;
                }
                SelectActiveEmployee(employee);
            }
        });

        public ICommand ActivateEmployeeCommand => new RelayCommand(() =>
        {
            FilteredInactiveEmployees = InactiveEmployees;
            IsActivatingEmp = true;
            SelectedActiveEmployee = null;
        });

        public ICommand DiscardEmployeeCommand => new RelayCommand<Employee>((employee) =>
        {
            if (employee != null && employee != GENERAL_EMPLOYEE)
            {
                InactiveEmployees.Add(employee);
                ActiveEmployees.Remove(employee);
                SelectedActiveEmployee = GENERAL_EMPLOYEE;
            }
        });

        public ICommand ActivateSelectedEmpCommand => new RelayCommand<Employee>((employee) =>
        {
            if (employee != null && employee != GENERAL_EMPLOYEE)
            {
                ActiveEmployees.Add(employee);
                InactiveEmployees.Remove(employee);
                CloseEmpActivision();
            }
        });

        public ICommand CancelEmpActivisionCommand => new RelayCommand(() =>
        {
            CloseEmpActivision();
        });

        #endregion Commands

        private void SelectActiveEmployee(Employee employee)
        {
            SelectedActiveEmployee = employee;
            SelectedActiveEmployee.IsSelected = true;
        }

        private void FilterInactiveEmployees()
        {
            if (!string.IsNullOrEmpty(SearchText))
            {
                FilteredInactiveEmployees = InactiveEmployees.Where(employee =>
                                                employee.Name.ToLower().Contains(SearchText.ToLower()));
            }
            else
            {
                FilteredInactiveEmployees = InactiveEmployees;
            }
        }

        private void CloseEmpActivision()
        {
            IsActivatingEmp = false;
            SelectedActiveEmployee = GENERAL_EMPLOYEE;
        }
    }
}
