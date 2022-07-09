using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Meisters.Models
{
    class Employee
    {
        public Employee(string name, bool isAdmin = false, uint uid = 0)
        {
            Name = name;
            IsAdmin = isAdmin;
            Uid = uid;
        }

        public string Name { get; set; }
        public uint Uid { get; set; }
        public bool IsAdmin { get; set; }
        public bool IsSelected { get; set; } = false;
    }
}
